#pragma once
#include "NewUserRequest.h"



NewUserRequest::NewUserRequest(QByteArray& request, DAL* d) :AbstractRequest(request, d)
{
	income_data_ = Parser::ParseAsLoginOrRegisterInfo(request);
	prepareResponse();
}
bool NewUserRequest::sendResponde(QTcpSocket * initByClient)
{
	outcome_data_.append(Parser::GetUnpossibleSequence());
	initByClient->write(outcome_data_);
	initByClient->waitForBytesWritten(3000);
	initByClient->disconnectFromHost();
	return true;
}
//return - will responde with 0 if everything is done good or -1 if something failed
//receives - 0#userName#passWord
//switch(firstbyte)

void NewUserRequest::prepareResponse()
{
	Client newClient;
	newClient.setUserId(income_data_.id);
	newClient.setUserPassword(income_data_.password);
	newClient.setUserIp(income_data_.ip);
	newClient.setUserPort(income_data_.port);
	//int sizeBeforeAdding = database->getSize();
	database->setClient(newClient);
	//if (sizeBeforeAdding != database->getSize()) { //addition success
		outcome_data_ = Parser::yesNoResponseToByteArray((quint8)ServerRequests::REGISTER_SUCCEED);
	/*}
	else {
		//something goes wrong
		outcome_data_ = Parser::yesNoResponseToByteArray((quint8)ServerRequests::REGISTER_FAILED);
	}*/

}