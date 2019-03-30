#pragma once
#include "AbstractRequest.h"
// In one session:
// receives:  LOGIN,//+LoginInfo(c->s)I
// respond:  (1) LOGIN_SUCCEED,//empty(s->c)LOGIN
//           (2) LOGIN_FAILED,//empty(s->c)LOGIN
//           (3) NEW_FRIEND_INFO//+NewFriendInfo(s->c)I,-FRIENDSHIP_ACCEPTED||-FRIENDSHIP_REJECTED; notify about new friend
//           (4) ADD_FRIEND_REQUEST,//+AddFriendInfo(s->c)I,-FRIEND_REQUEST; -if hase pending friend requests;
// in other session:
//           (5) FRIEND_UPDATE_INFO//+FriendUpdateInfo(s->c)I,-LOGIN; -say "Im online" to all
// work: 
//      -check client by id and password; if fail, respond - (2);if ok, respond (1); 
//      -write LoginInfo in db; 
//      -check all pending queues releted to currently connected user and send to him (3) or (4);
//      -disconect from peson who currently logining
//      -fetch all friends of that client and send them (3)
//
class LoginRequest : public AbstractRequest {
public:
	
	LoginRequest(QByteArray& A, DAL*, QTcpSocket*);  
	bool SendResponde();
  bool SendToFriend(QTcpSocket &output_socket, QByteArray raw_data, unsigned int id);
protected:
	void PrepareResponse();
private:

  void SendingPendingFriendRequests();
  void SendingPendingNotifications();

	LoginInfo incoming_structure_;	
	FriendUpdateInfo send_to_friends_;  
	Client requester_; 
	quint8 response_to_requester_;  
};