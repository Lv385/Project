#include "ServerThread.h"
#include <QTcpSocket>
#include <sstream>
#include "RequestProcessing/NewUserRequest.h"
#include "RequestProcessing/LoginRequest.h"


ServerThread::ServerThread(int socket_descriptor, QObject *parent) : QThread(parent),socket_descriptor_(socket_descriptor)
{
	dal_ = new DAL();
	qDebug() << "New server thread created!\n";

}


void ServerThread::run()
{
	QTcpSocket incomming_connection;
	incomming_connection.setSocketDescriptor(socket_descriptor_);
	
	if (incomming_connection.waitForReadyRead(10000)) 
	{
		qDebug() << "waitForReadyRead";
		data_ = incomming_connection.readAll();
		SetRequest(Parser::getRequestType(data_));

		request_->sendResponde(&incomming_connection);
		//dal_.printDatabase();t
	}
}

void ServerThread::SetRequest(quint8 type)
{	
	switch (type)
	{
	case (quint8)ClientRequest::REGISTER: // should be register
		request_ = new NewUserRequest(data_, dal_); 
		break;
	case (quint8)ClientRequest::LOGIN:
		qDebug() << "loginrequest";
		request_ = new LoginRequest(data_, dal_);

	}
}


ServerThread::~ServerThread()
{
	delete request_;
}
