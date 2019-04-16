#pragma once
#include "abstract_request.h"
#include "../Parser&Structs/parser.h"
//In one session:
//receives: REGISTER,//+RegisterInfo(c->s)I
//respond:  (1)REGISTER_SUCCEED,//+RegisterSuccessInfo(s->c)REGISTER
//          (2)REGISTER_FAILED,  // empty(s->c)REGISTER
//work: try to write RegisterInfo to DB; if fail, respond - (1); 
//      if ok, respond (2)
    class NewUserRequest : public AbstractRequest {
public:
	NewUserRequest(QByteArray& , DAL*, QTcpSocket* );
	bool SendResponde();
protected:
	void PrepareResponse();
private:
	RegisterInfo income_data_;
	QByteArray outcome_data_;
	bool user_exist;
};
