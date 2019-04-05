#include "LoginRequest.h"


LoginRequest::LoginRequest(QByteArray& A, DAL* d, QTcpSocket* s)
    : AbstractRequest(d, s) {
  incoming_structure_ = Parser::ParseAsLoginInfo(A);
  PrepareResponse();  
  QString IP_ = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();
  QString logstring = IP_+"::"+Logger::ConvertQuint16ToString(incoming_structure_.port);
  Logger::LogOut(logstring, A);
}

//done with nuanses means that need to test update under friends requests 
void LoginRequest::PrepareResponse() {
  // check user in db  and set t or f
  try {
    requester_ = database_->getClient(incoming_structure_.id);
    if (QString::compare(requester_.password,
                         incoming_structure_.password) == 0) {
      // pasword are correct
      requester_.ip   = client_socket_->peerAddress().toString();
      requester_.port = incoming_structure_.port;
      database_->UpdateClient(requester_);  // updating ip::port
      response_to_requester_ = (quint8)ServerRequest::LOGIN_SUCCEED;
    } else {
      // incorrect password
      response_to_requester_ = (quint8)ServerRequest::LOGIN_FAILED;
    }
  } catch (UserNotFound& e) {
    response_to_requester_ = (quint8)ServerRequest::LOGIN_FAILED;
    qDebug() << e.what();
  }
}

bool LoginRequest::SendResponde() {
  if (response_to_requester_ == (quint8)ServerRequest::LOGIN_SUCCEED) {
    QByteArray b =
        Parser::Empty_ToByteArray((quint8)ServerRequest::LOGIN_SUCCEED);
    b.append(Parser::GetUnpossibleSequence());

    QString ip = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();   
    QString logstring_ = ip + "::" + Logger::ConvertQuint16ToString(incoming_structure_.port);
    Logger::LogOut(logstring_, b);

    client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    SendingPendingFriendRequests(); // done
    SendingPendingNotifications();// dont working
    client_socket_->disconnectFromHost();

    // sending FriendUpdateInfo to all friends
    requester_ = database_->getClient(requester_.login);
    send_to_friends_.id = requester_.id;
    send_to_friends_.ip = requester_.ip;
    send_to_friends_.port = requester_.port;
    QByteArray raw_data = Parser::FriendUpdateInfo_ToByteArray(send_to_friends_);
    raw_data.append(Parser::GetUnpossibleSequence());
    QVector<UsersID> currentFriends = requester_.friends;
    QTcpSocket output_socket;  // for friends
    for (unsigned i = 0; i < currentFriends.size(); i++) {
      SendToFriend(output_socket, raw_data, currentFriends[i].second_user_id);
      // zrobiti kilkist potokiv vidpovidno do kilkosti druziv
    }   

  } else {
    // sending ServerRequests::LOGIN_FAILED
    QByteArray b = Parser::Empty_ToByteArray(response_to_requester_);
    b.append(Parser::GetUnpossibleSequence());
    
    QString Ip_ = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();
    QString Logstring= Ip_ + "::" + Logger::ConvertQuint16ToString(incoming_structure_.port);
    Logger::LogOut(Logstring, b);
    client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    // client_socket_->disconnectFromHost();
  }
  return true;
}
//DONe
bool LoginRequest::SendToFriend(QTcpSocket& output_socket, QByteArray raw_data, 
                                unsigned int id) { 
 
  User tempClient = database_->getClient(id);
  qDebug()<<Logger::Log_User(tempClient)<<"\n";
  output_socket.connectToHost(tempClient.ip, tempClient.port);
  if (output_socket.waitForConnected(5000)) { // default is 5000 but this thing is makes bigger time of login req execution 
    
    QString ip = QHostAddress(output_socket.peerAddress().toIPv4Address(false)).toString();
    QString Logstring_ = ip + "::" + Logger::ConvertQuint16ToString(tempClient.port);
    Logger::LogOut(Logstring_, raw_data);                     
    
    output_socket.write(raw_data);
    output_socket.waitForBytesWritten(1000);
    output_socket.disconnectFromHost();
  }

  return false;
}
//test (response sending is okay)
void LoginRequest::SendingPendingFriendRequests() {
  // this function should send to requester pending requests and pending
  // notifications
  // QTcpSocket notifiying_requester;
  QVector<UsersID> pendsreqs = requester_.requests;  // theese guys want to be friends
  QByteArray raw_data;

  for (int i = 0; i < pendsreqs.size(); i++) {
    AddFriendInfo possible_friend;
    User tmp = database_->getClient(pendsreqs[i].first_user_id); //taking possible friend
    possible_friend.requester_login = tmp.login;
    possible_friend.requester_id = tmp.id;
    raw_data = Parser::AddFriendInfo_ToByteArray(possible_friend);
    raw_data.append(Parser::GetUnpossibleSequence());

    QString ip__ = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();    
    QString logstring__ = ip__ + "::" + Logger::ConvertQuint16ToString(incoming_structure_.port);
    Logger::LogOut(logstring__,raw_data);
   
    client_socket_->write(raw_data);
    client_socket_->waitForBytesWritten(1000);
  }
}
//test
void LoginRequest::SendingPendingNotifications() {
  // fetch data about that users, construct
  // FRIEND_UPDATE_INFO//+FriendUpdateInfo out of them and send it to currently
  // connected client
  QVector<UsersID> pend_notif = requester_.notification; //is 0 why?
  QByteArray raw_data;

  for (int i = 0; i < pend_notif.size(); i++) {
    NewFriendInfo from_new_friend;
    User tmp = database_->getClient(pend_notif[i].first_user_id);
    from_new_friend.id = tmp.id;
    from_new_friend.ip = tmp.ip;
    from_new_friend.login = tmp.login;
    from_new_friend.port = tmp.port;
    raw_data = Parser::NewFriendInfo_ToByteArray(from_new_friend);
    raw_data.append(Parser::GetUnpossibleSequence());

    QString Ip__ = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();
    QString Logstring__ = Ip__ + "::" + Logger::ConvertQuint16ToString(incoming_structure_.port);
    Logger::LogOut(Logstring__, raw_data);

    client_socket_->write(raw_data);
    client_socket_->waitForBytesWritten(1000);
  }
}
