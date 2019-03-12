#pragma once
#include "NewUserRequest.h"



NewUserRequest::NewUserRequest(QByteArray& request, DAL* d) :AbstractRequest(request, d)
{
    income_data_ = Parser ::ParseAsRegisterInfo(request);
	prepareResponse();
} //port login password  // ip

void NewUserRequest::prepareResponse()
{
	Client newClient;
    newClient.SetUserPort(income_data_.port);
    newClient.SetUserName(income_data_.login);
	newClient.SetUserPassword(income_data_.password);
	//newClient.SetUserIp(income_data_.ip); must be added!!!
	
	if (database->Check_If_Client_exists_In_Db(newClient) == false) { // if client not exist
		database->SetClient(newClient);
		outcome_data_ = Parser::yesNoResponseToByteArray((quint8)ServerRequests::REGISTER_SUCCEED);
		outcome_data_.append(database->GetClientId(newClient)); // id of just registered user
		outcome_data_.append(Parser::GetUnpossibleSequence());

	}
	else {

		outcome_data_ = Parser::yesNoResponseToByteArray((quint8)ServerRequests::REGISTER_FAILED);
		outcome_data_.append(Parser::GetUnpossibleSequence());
	}
}
bool NewUserRequest::sendResponde(QTcpSocket * initByClient)
{
	initByClient->write(outcome_data_);
	initByClient->waitForBytesWritten(3000);
	initByClient->disconnectFromHost();
	return true;
}
// old variant is down in comments
//bool NewUserRequest::sendResponde(QTcpSocket * initByClient)
//{
//	outcome_data_.append(Parser::GetUnpossibleSequence());
//	initByClient->write(outcome_data_);
//	initByClient->waitForBytesWritten(3000);
//	initByClient->disconnectFromHost();
//	return true;
//}
//
//void NewUserRequest::prepareResponse()
//{
//	Client newClient;
//	newClient.SetUserId(income_data_.id);
//	newClient.SetUserPassword(income_data_.password);
//	newClient.SetUserIp(income_data_.ip);
//	newClient.SetUserPort(income_data_.port);
//	//int sizeBeforeAdding = database->getSize();
//	database->SetClient(newClient);
//	//if (sizeBeforeAdding != database->getSize()) { //addition success
//		outcome_data_ = Parser::yesNoResponseToByteArray((quint8)ServerRequests::REGISTER_SUCCEED);
//		outcome_data_.append(Parser::GetUnpossibleSequence());
//	/*} else {
//		//something goes wrong
//		outcome_data_ = Parser::yesNoResponseToByteArray((quint8)ServerRequests::REGISTER_FAILED);
//		outcome_data_.append(Parser::GetUnpossibleSequence());
//	}*/
//
//}