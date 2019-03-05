#pragma once
#include "AbstractRequest.h"

class LoginRequest : public AbstractRequest {
public:
	LoginRequest(QByteArray&A);

	bool sendResponde(QTcpSocket*);
protected:
	void prepareResponse();
private:
	LoginInfo log;
	bool logcheck;
};