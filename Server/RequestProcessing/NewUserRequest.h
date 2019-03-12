#pragma once
#include "AbstractRequest.h"
#include "../Parser&Structs/parser.h"

//WOULD NOT WORK WITHOUT NeW Register Structure and Register parser
class NewUserRequest : public AbstractRequest {
public:
	NewUserRequest(QByteArray& , DAL* );
	bool sendResponde(QTcpSocket*);
protected:
	void prepareResponse();
private:
    Registration income_data_;
	QByteArray outcome_data_;
	bool user_exist;
};