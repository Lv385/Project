#include "LoginRequest.h"
//need to add  notifiying loginned user 
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

       SendToFriend(output_socket,raw_data,currentFriends[i]); 
       // zrobiti kilkist potokiv vidpovidno do kilkosti druziv 
    }
   // output_socket.close();

    // Consider situation when one user(A) has pending friend notification from
    // other user(B) and thay will login simultaneously. In such case A will
    // receive FriendUpdateInfo (FUI)
    // from B because they are friends already. But than server will send FUI
    // removed from pending friend notification vector (wich belongs to A) AGAIN
    // during A login processing as  SendingPendingRequests() will define. So we need
    // to remove FUI from pending friend notification vector (wich belongs to A)
    // during main statements execution releted to B. So check
    // tempClient.pending_friend_notifications_ for requester_.id and remove it
    // on coincidence 


    //should be the last call. Perform all pending queues check there!!!
    SendingPendingRequests(output_socket); // should add pending notifiying

  } else {
    //sending ServerRequests::LOGIN_FAILED
    QByteArray b = Parser::Empty_ToByteArray(response_to_requester_);
    b.append(Parser::GetUnpossibleSequence());
    Logger::LogOut(b);
    client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    //client_socket_->disconnectFromHost();
  }
  return true;
}

bool LoginRequest::SendToFriend(QTcpSocket &output_socket,QByteArray raw_data,unsigned int id)
{
  Client tempClient = database_->getClient(id);
  output_socket.connectToHost(tempClient.GetUserIp(), tempClient.GetUserPort());
  if (output_socket.waitForConnected(5000)) {
    Logger::LogOut(raw_data);
    output_socket.write(raw_data);
    output_socket.waitForBytesWritten(1000);
    output_socket.disconnectFromHost();
  }

  return false;
}

void LoginRequest::SendingPendingRequests(QTcpSocket &notifiying_requester) {
  
  // this function should send to requester pending requests and pending notifications 
 // QTcpSocket notifiying_requester;
  QVector<uint> pendsreqs= requester_.Get_Pending_Requests(); // theese guys want to be friends 
  QByteArray raw_data;
  notifiying_requester.connectToHost(requester_.GetUserIp(), requester_.GetUserPort());

  for (int i = 0; i < pendsreqs.size(); i++)
  {
     AddFriendInfo possible_friend;
     Client tmp = database_->getClient(pendsreqs[i]);
     possible_friend.requester_login = tmp.GetUserName();
     possible_friend.requester_id = tmp.GetUserId();
     raw_data = Parser::AddFriendInfo_ToByteArray(possible_friend);
     raw_data.append(Parser::GetUnpossibleSequence());
     if (notifiying_requester.waitForConnected(5000)) {
        Logger::LogOut(raw_data);
        notifiying_requester.write(raw_data);
        notifiying_requester.waitForBytesWritten(1000);
      }
 }
  notifiying_requester.disconnectFromHost();
 
}

void LoginRequest::SendingPendingNotifications(QTcpSocket & notifiying_requester)
{
  // this function is for notification of client that he has some news about his friend requests
}
