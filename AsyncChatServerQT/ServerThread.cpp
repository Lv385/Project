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
	
	if (incomming_connection.waitForReadyRead(3000)) 
	{
		data_ = incomming_connection.readAll();
		AbstractRequest* request;
		SetRequest(Parser::getRequestType(data_));

		request_->sendResponde(&incomming_connection);
		dal_.printDatabase();
	}
}

void ServerThread::SetRequest(quint8 type)
{	
	switch (type)
	{
	case (quint8)ClientRequest::LOGIN: // should be register
		request_ = new NewUserRequest(data_, dal_);
	}
}


ServerThread::~ServerThread()
{
	delete request_;
}
