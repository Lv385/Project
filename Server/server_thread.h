#pragma once
#include <QThread>
#include <string>
#include <vector>
#include "RequestProcessing/abstract_request.h"
#include "../Parser&Structs/parser.h"

class ServerThread:public QThread
{
	Q_OBJECT
public:
	ServerThread( int socket_descriptor, QObject *parent);
	void run() override;
	//creats new subclass of AbstractRequest depending on a value encoded in a incomming connection data
	void SetRequest(quint8 type, QTcpSocket*);
	~ServerThread();

private:
	int socket_descriptor_;
	DAL dal_;
  //raw data recevied by server
	QByteArray data_;
  //handler for a class that incapsulate request processing logic 
  //will be initialized to current subclass depending on recevied raw data
	AbstractRequest* request_;  
};

