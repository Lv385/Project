#pragma once
#include "AbstractRequest.h"


class NewUserRequest : public AbstractRequest {
public:
	NewUserRequest(std::vector<std::string>&, DAL&);
	bool sendResponde(QTcpSocket*);
protected:
	void prepareResponse();
private:
	std::string response;
};