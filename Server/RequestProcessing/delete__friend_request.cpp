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
  }
  

}
bool DeleteFriendRequest::SendResponde()
{

  return false;
}

