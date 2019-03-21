#pragma once
#include "AbstractRequest.h"
// In one session:
// receives:  LOGIN,//+LoginInfo(c->s)I
// respond:  (1) LOGIN_SUCCEED,//empty(s->c)LOGIN
//           (2) LOGIN_FAILED,//empty(s->c)LOGIN
//In other sessions:
//           (3) FRIEND_UPDATE_INFO//+FriendUpdateInfo(s->c)I,-LOGIN ;
// work: check client by id and password; if fail, respond - (2);
//      if ok, respond (1); write LoginInfo in db; fetch all friends of 
//      that client and send them (3)
class LoginRequest : public AbstractRequest {
public:
	
	LoginRequest(QByteArray& A, DAL*, QTcpSocket*);

	bool SendResponde();
  bool SendToFriend(QTcpSocket &output_socket, QByteArray raw_data, unsigned int id);
protected:
	void PrepareResponse();
private:
  void DoAdditionalTasks(QTcpSocket&notifiying_requester);

	LoginInfo incoming_structure_;	
	FriendUpdateInfo toSend_;
	Client requester_; 
	quint8 response_to_requester_;
};