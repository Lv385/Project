#include "ServerThread.h"
#include <QTcpSocket>
#include <sstream>
#include "RequestProcessing/NewUserRequest.h"


ServerThread::ServerThread(int socket_descriptor, DAL& dal, QObject *parent) : QThread(parent),dal_(dal),socket_descriptor_(socket_descriptor)
{
	qDebug() << "New server thread created!\n";
}


void ServerThread::run()
{
	
	QTcpSocket incomming_connection;
	incomming_connection.setSocketDescriptor(socket_descriptor_);
	
	if (incomming_connection.waitForReadyRead(3000)) {
		QString client_input(incomming_connection.readAll());
		ParseString(client_input.toStdString());
		AbstractRequest* request_processor = getRequestProcessor();
		if (request_processor != nullptr) {
			request_processor->sendResponde(&incomming_connection);
			delete request_processor;
		}
		dal_.printDatabase();
	}
}

void ServerThread::ParseString(const std::string & request)
{
	qDebug() << "Incoming message :" << QString::fromUtf8(request.c_str()) << "\n";
	std::istringstream iss(request);
	std::string token;
	while (std::getline(iss, token, '#'))
	{	
		parsed_request_.push_back(token);
	}
	//for debug -display parsed vector content
	/*
	qDebug() << "Parsed vector content \n";
	for (auto i = parsed_request_.begin(); i != parsed_request_.end(); ++i) {
		qDebug() << QString::fromUtf8((*i).c_str()) << ' ';
	}
	qDebug() << "\n\n";
	*/
}

AbstractRequest * ServerThread::getRequestProcessor()
{
	if (parsed_request_[0] == "0") {
		return new NewUserRequest(parsed_request_, dal_);
	}
	return nullptr;
}

ServerThread::~ServerThread()
{
}
