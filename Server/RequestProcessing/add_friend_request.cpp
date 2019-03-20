#include "add_friend_request.h"

AddFriendRequest::AddFriendRequest(QByteArray &request, DAL *d, QTcpSocket *s)
    : AbstractRequest(d, s) {
  income_data_ = Parser::ParseAsFriendRequestInfo(request);
  PrepareResponse();
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
      info_to_send.requester_ip = sender_guy.GetUserIp();
      info_to_send.requester_login = sender_guy.GetUserName();
      info_to_send.requester_port = sender_guy.GetUserPort();
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
    Logger::LogOut(b);
    client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    client_socket_->disconnectFromHost();

    //sending ADD_FRIEND_REQUEST,//+AddFriendInfo(s->c)I,-FRIEND_REQUEST;    
    QTcpSocket output_socket;
    output_socket.connectToHost(requested_guy.GetUserIp(), requested_guy.GetUserPort());

    if (output_socket.waitForConnected(5000)) {  // check if can connect if yes -> send add friend
      Logger::LogOut(send_addfriend_info_bytearr);
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
    Logger::LogOut(b);
    client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    client_socket_->disconnectFromHost();
  }
  
  
  
    return false;
}
