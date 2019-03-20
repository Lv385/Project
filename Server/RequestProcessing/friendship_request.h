#pragma once
#include "AbstractRequest.h"
#include "../Parser&Structs/parser.h"  
                          
// In one session:
// receives:  (1) FRIENDSHIP_ACCEPTED,//+FriendRequestInfo(c->s)ADD_FRIEND_REQUEST^, -prc friendship_request
//            (2) FRIENDSHIP_REJECTED,//+FriendRequestInfo_(c->s)ADD_FRIEND_REQUEST^, -prc friendship_request
// respond:   (3) FRIEND_UPDATE_INFO//+FriendUpdateInfo(s->c)I,-LOGIN ; 
//           
// work: -deterrmine what kind of request we are receiving (1 or 2);
//       -if (1)||(2) fetch FriendRequestInfo.other_login (that login is the copy of
//        AddFriendInfo.requester_login that client receive as a result of add_friend_request)
//        and find its id -(other.id);
//       -check FriendRequestInfo.id and write (other.id) to his friend;
//       -check (other.id) and write FriendRequestInfo.id to his friend;
//       -responde to FriendRequestInfo.id with (3) filled by information related to (other.id)
//       -if (2) - do nothing at this moment (will be improved later) 
//In other session:
//       - send(3) to (other.id) filled by information related to FriendRequestInfo.id
//       -if connection failed - save (other.id) and FriendRequestInfo.id
//        into pending_friend_notifications_

class FriendshipRequest : public AbstractRequest {
 public:
  FriendshipRequest(QByteArray& request, DAL*, QTcpSocket*);
  bool SendResponde();
 protected:
  void PrepareResponse();
 private:
  FriendRequestInfo income_data_;
  FriendUpdateInfo outcome_for_requester_;
  FriendUpdateInfo outcome_for_new_friend_;
  QByteArray outcome_data_;
  Client requester_;
  Client new_friend_;
  quint8 request_type_;
  bool doNothing_;
  ;
};
