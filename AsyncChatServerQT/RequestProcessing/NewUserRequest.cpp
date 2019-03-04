#pragma once
#include "NewUserRequest.h"



NewUserRequest::NewUserRequest(std::vector<std::string>& request, DAL& d) :AbstractRequest(request, d)
{
	prepareResponse();
}
bool NewUserRequest::sendResponde(QTcpSocket * initByClient)
{

	initByClient->write(response.c_str());
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
	newClient.setUserName(request[1]);
	newClient.setUserPassword(request[2]);
	//newClient.setUserIp(request[3]);
	//newClient.setUserPort(request[4]);
	int sizeBeforeAdding = database.getSize();
	database.setClient(newClient);
	if (sizeBeforeAdding != database.getSize()) { //addition success
		response = "0";
	}
	else {
		//something goes wrong
		response = "-1";
	}

}