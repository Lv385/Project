#pragma once
#include "AbstractRequest.h"

class LoginRequest : public AbstractRequest {
public:
	
	LoginRequest(QByteArray&A, DAL*);

	bool sendResponde(QTcpSocket*);
protected:
	void prepareResponse();
private:
	LoginOrRegisterInfo log_;
	//FRIEND_UPDATE_INFO
	FriendUpdateInfo toSend_;
	Client requester_; 
	bool logcheck;
};