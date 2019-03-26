#pragma once
#include "AbstractRequest.h"
#include "../Parser&Structs/parser.h"
// In one session:
// receives:  FRIEND_REQUEST,//+FriendRequestInfo(c->s)I,-user
// respond:  (1) FRIEND_REQUEST_FAILED,//empty(s->c)FRIEND_REQUEST; 
//           (2) FRIEND_REQUEST_SUCCEED,//empty(s->c)FRIEND_REQUEST;
// In other sessions:
//           (3) ADD_FRIEND_REQUEST,//+AddFriendInfo(s->c)I,-FRIEND_REQUEST;
// work: check client by id and password; if fail, respond - (1);
//       check FriendRequestInfo.other_login if exist in db; ok responde -(2);fail responde -(1)      
// In other session:
//      if preciouse responde was(2), prepare AddFriendInfo, connect to FriendRequestInfo.other_login
//      and write to him (3)
//      if connection failed - save FriendRequestInfo.other_login.id and FriendRequestInfo.id
//      into pending_friend_request


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