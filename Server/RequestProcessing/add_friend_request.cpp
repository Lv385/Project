#include "add_friend_request.h"

AddFriendRequest::AddFriendRequest(QByteArray &request, DAL *d, QTcpSocket *s)
    : AbstractRequest(d, s) {
  income_data_ = Parser::ParseAsFriendRequestInfo(request);
  PrepareResponse();
  QString IP = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();
  QString logstring = IP + "::xxx";
  Logger::LogOut(logstring, request);
}

void AddFriendRequest::PrepareResponse() {
  // FriendRequestInfo ;
  // other_login
  // id
  // password
  try {
    // he actually loginned so uptodated data is in db
    sender_guy = database_->getClient(income_data_.id);  
    //TODO: check if parties are not friends allready!!!!!
    if (QString::compare(sender_guy.GetUserPassword(), income_data_.password) == 0) {
      requested_guy = database_->getClient(income_data_.other_login);
      info_to_send.requester_id = sender_guy.GetUserId();
      info_to_send.requester_login = sender_guy.GetUserName();
      send_addfriend_info_bytearr = Parser::AddFriendInfo_ToByteArray(info_to_send);
      response_to_requester_ = (quint8)ServerRequests::FRIEND_REQUEST_SUCCEED;
    } else {
      response_to_requester_ = (quint8)ServerRequests::FRIEND_REQUEST_FAILED;
      // because password is incorrect
    }
  } catch (UserNotFound &e) {
    response_to_requester_ = (quint8)ServerRequests::FRIEND_REQUEST_FAILED;
    qDebug() << e.what();
  }
}
bool AddFriendRequest::SendResponde() {
  if (response_to_requester_ == (quint8)ServerRequests::FRIEND_REQUEST_SUCCEED) {
    QByteArray b = Parser::Empty_ToByteArray( (quint8)ServerRequests::FRIEND_REQUEST_SUCCEED);
    b.append(Parser::GetUnpossibleSequence());

    QString ip = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();
    QString logstring_ = ip + "::xxx";
    Logger::LogOut(logstring_, b);

    client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    client_socket_->disconnectFromHost();

    //sending ADD_FRIEND_REQUEST,//+AddFriendInfo(s->c)I,-FRIEND_REQUEST;    
    QTcpSocket output_socket;
    output_socket.connectToHost(requested_guy.GetUserIp(), requested_guy.GetUserPort());    
    
    QString Logstring_ = QHostAddress(requested_guy.GetUserIp().toIPv4Address(false)).toString()+ "::" + Logger::ConvertQuint32ToString(requested_guy.GetUserPort());
    Logger::LogOut(Logstring_, send_addfriend_info_bytearr);

    if (output_socket.waitForConnected(5000)) {  // check if can connect if yes -> send add friend     
      output_socket.write(send_addfriend_info_bytearr);
      output_socket.waitForBytesWritten(1000);
      output_socket.disconnectFromHost();
    } else {
      // go and write  info about this request into db
      requested_guy.AddPendingFriendRequest(sender_guy);
      database_->UpdateClient(requested_guy);
    }
    output_socket.close();
    // IMPORTANT!!!!   Dopilit login with checking  if user had any issues to
    // him
  } else {
    QByteArray b = Parser::Empty_ToByteArray((quint8)ServerRequests::FRIEND_REQUEST_FAILED);
    b.append(Parser::GetUnpossibleSequence());

    QString Ip = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();
    QString logstrin = Ip + "::" + Logger::ConvertQuint32ToString(sender_guy.GetUserPort());
    Logger::LogOut(logstrin, b);

    client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    client_socket_->disconnectFromHost();
  }
    return false;
}
