#include "LoginRequest.h"

LoginRequest::LoginRequest(QByteArray& A, DAL* d, QTcpSocket* s)
    : AbstractRequest(d, s) {
  incoming_structure_ = Parser::ParseAsLoginInfo(A);
  PrepareResponse();
}

void LoginRequest::PrepareResponse() {
  // check user in db  and set t or f
  try {
    requester_ = database_->getClient(incoming_structure_.id);
    if (QString::compare(requester_.GetUserPassword(),
                         incoming_structure_.password) == 0) {
      // pasword are correct
      requester_.SetUserIp(client_socket_->peerAddress());
      requester_.SetUserPort(incoming_structure_.port);
      database_->UpdateClient( requester_);  // updating ip::port
      response_to_requester_ = (quint8)ServerRequests::LOGIN_SUCCEED;
    } else {
      //incorrect password
      response_to_requester_ = (quint8)ServerRequests::LOGIN_FAILED;
    }
  } catch (UserNotFound& e) {
    response_to_requester_ = (quint8)ServerRequests::LOGIN_FAILED;
    qDebug() << e.what();
  }
}
bool LoginRequest::SendResponde() {  
  if (response_to_requester_ == (quint8)ServerRequests::LOGIN_SUCCEED) {
    QByteArray b =
        Parser::Empty_ToByteArray((quint8)ServerRequests::LOGIN_SUCCEED);
    b.append(Parser::GetUnpossibleSequence());
    Logger::LogOut(b);
    client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    client_socket_->disconnectFromHost();

    requester_ = database_->getClient(requester_.GetUserName());
    toSend_.id = requester_.GetUserId();
    toSend_.ip = requester_.GetUserIp();
    toSend_.port = requester_.GetUserPort();

    QByteArray raw_data = Parser::FriendUpdateInfo_ToByteArray(toSend_);
    raw_data.append(Parser::GetUnpossibleSequence());

    QVector<unsigned int> currentFriends = requester_.GetFriends();
    QTcpSocket output_socket;
    for (unsigned i = 0; i < currentFriends.size(); i++) {
      Client tempClient = database_->getClient(currentFriends[i]);
      output_socket.connectToHost(tempClient.GetUserIp(),
                                  tempClient.GetUserPort());
      if (output_socket.waitForConnected(5000)) {
        Logger::LogOut(raw_data);
        output_socket.write(raw_data);
        output_socket.waitForBytesWritten(1000);  
        output_socket.disconnectFromHost();
      }
    }
    output_socket.close();
  } else {
    //sending ServerRequests::LOGIN_FAILED
    QByteArray b = Parser::Empty_ToByteArray(response_to_requester_);
    b.append(Parser::GetUnpossibleSequence());
    Logger::LogOut(b);
    client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    client_socket_->disconnectFromHost();
  }
  return true;
}
