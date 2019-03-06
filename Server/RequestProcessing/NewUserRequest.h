#pragma once
#include "AbstractRequest.h"
#include "../Parser&Structs/parser.h"


class NewUserRequest : public AbstractRequest {
public:
	NewUserRequest(QByteArray& , DAL* );
	bool sendResponde(QTcpSocket*);
protected:
	void prepareResponse();
private:
	LoginOrRegisterInfo income_data_;
	QByteArray outcome_data_;
};