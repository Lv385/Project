#pragma once
#include "abstract_request.h"
class DeleteFriendRequest :public AbstractRequest
{

  public:
    DeleteFriendRequest(QByteArray&, DAL*, QTcpSocket*);
    bool SendResponde();
  protected:
    void PrepareResponse();
  private:
    FriendRequestInfo income_data_;
    User requester_;
    User deleted_friend;
    quint8 response_to_requester_;
};

