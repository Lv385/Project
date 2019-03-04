#pragma once
#include <QThread>
#include <string>
#include <vector>
#include "RequestProcessing/AbstractRequest.h"
#include "../Parser&Structs/parser.h"

class ServerThread:public QThread
{
	Q_OBJECT
public:
	ServerThread( int socket_descriptor, DAL& dal, QObject *parent);
	void run() override;
	void ParseString(const std::string & request);
	AbstractRequest* getRequestProcessor();
	void SetRequest(quint8 type);
	~ServerThread();

private:
	int socket_descriptor_;
	DAL& dal_;
	QByteArray data_;
	AbstractRequest* request_;
};

