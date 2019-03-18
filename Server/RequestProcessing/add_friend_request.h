#pragma once
#include "AbstractRequest.h"
#include "../Parser&Structs/parser.h"

class AddFriendRequest : public AbstractRequest {
public:
  AddFriendRequest(QByteArray&, DAL*, QTcpSocket*);
  bool SendResponde();
protected:
  void PrepareResponse();
private:
  FriendRequestInfo income_data_;
  QByteArray send_addfriend_info_bytearr;
  AddFriendInfo info_to_send;
  Client sender_guy;
  quint8 response_to_requester_;
  Client requested_guy;
};