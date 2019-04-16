#include "delete_friend_request.h"

DeleteFriendRequest::DeleteFriendRequest(QByteArray& request, DAL* d, QTcpSocket* s)
  : AbstractRequest(d, s) {

  income_data_ = Parser::ParseAsFriendRequestInfo(request);
  PrepareResponse();
  QString IP = QHostAddress(client_socket_->peerAddress().toIPv4Address(false)).toString();
  QString logstring = IP + "::xxx";
  Logger::LogOut(logstring, request);

}

void DeleteFriendRequest::PrepareResponse()
{
  requester_ = database_->getClient(income_data_.id);
  deleted_friend = database_->getClient(income_data_.other_login);
  if(database_->CheckIfFriends(requester_,deleted_friend))
  {
    response_to_requester_ = (quint8)ServerRequest::DELETE_REQUEST_SUCCEED;
    for(int i=0;i<requester_.friends.size();i++)
    {
      if(requester_.friends[i].second_user_id == deleted_friend.id)
      {
         requester_.friends.remove(i);
      }
    }
    for (int i = 0; i < deleted_friend.friends.size(); i++)
    {
      if (deleted_friend.friends[i].second_user_id == requester_.id)
      {
        deleted_friend.friends.remove(i);
      }
    }
    database_->UpdateClient(requester_);
    database_->UpdateClient(deleted_friend);
  } else {
    response_to_requester_ = (quint8)ServerRequest::DELETE_REQUEST_FAILED;
  }
  

}
bool DeleteFriendRequest::SendResponde()
{
  // should add sending to deleted that he was deleted
  if(response_to_requester_== (quint8)ServerRequest::DELETE_REQUEST_SUCCEED)
  {
    QByteArray b = Parser::Empty_ToByteArray((quint8)ServerRequest::DELETE_REQUEST_SUCCEED);
    b.append(Parser::GetUnpossibleSequence());
    client_socket_->write(b);
    client_socket_->waitForBytesWritten(1000);
    client_socket_->disconnectFromHost();

    DeleteNotificationInfo data;
    data.id = requester_.id;
    QByteArray deleting_notif = Parser::DeleteNotificationInfo_ToByteArray(data);  // deleting notif to byte array
    deleting_notif.append(Parser::GetUnpossibleSequence());

    QTcpSocket output_socket; // send structure with id
    output_socket.connectToHost(deleted_friend.ip,deleted_friend.port);
    if (output_socket.waitForConnected(5000)) {
      output_socket.write(deleting_notif);
      output_socket.waitForBytesWritten(1000);
      output_socket.disconnectFromHost();
    } else {
      // in future possibly add  data in table if cant connect
    }
  } else {
    QByteArray b = Parser::Empty_ToByteArray((quint8)ServerRequest::DELETE_REQUEST_FAILED);
    b.append(Parser::GetUnpossibleSequence());
    client_socket_->write(b);
    client_socket_->waitForBytesWritten(1000);
    client_socket_->disconnectFromHost();
  }
  

  return false;
}

