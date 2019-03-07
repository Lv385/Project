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

void NewUserRequest::prepareResponse()
{
	Client newClient;
	newClient.SetUserId(income_data_.id);
	newClient.SetUserPassword(income_data_.password);
	newClient.SetUserIp(income_data_.ip);
	newClient.SetUserPort(income_data_.port);
	//int sizeBeforeAdding = database->getSize();
	database->setClient(newClient);
	//if (sizeBeforeAdding != database->getSize()) { //addition success
		outcome_data_ = Parser::yesNoResponseToByteArray((quint8)ServerRequests::REGISTER_SUCCEED);
		outcome_data_.append(Parser::GetUnpossibleSequence());
	/*} else {
		//something goes wrong
		outcome_data_ = Parser::yesNoResponseToByteArray((quint8)ServerRequests::REGISTER_FAILED);
		outcome_data_.append(Parser::GetUnpossibleSequence());
	}*/

}