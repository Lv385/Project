#pragma once
#include <QThread>
#include <string>
#include <vector>
#include "RequestProcessing/AbstractRequest.h"

class ServerThread:public QThread
{
	Q_OBJECT
public:
	ServerThread( int socket_descriptor, DAL& dal, QObject *parent);
	void run() override;
	void ParseString(const std::string & request);
	AbstractRequest* getRequestProcessor();
	~ServerThread();
private:
	int socket_descriptor_;
	DAL& dal_;
	std::vector<std::string> parsed_request_;
};

