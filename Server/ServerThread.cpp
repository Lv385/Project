#include "ServerThread.h"
#include <QTcpSocket>
#include <sstream>
#include "RequestProcessing/NewUserRequest.h"
#include "RequestProcessing/LoginRequest.h"


ServerThread::ServerThread(int socket_descriptor, QObject *parent) : QThread(parent),socket_descriptor_(socket_descriptor)
{
	
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
          SetRequest(Parser::getRequestType(data_), &incomming_connection);
    
    
		request_->SendResponde();
    // Watch out!!! This thread should be alive till incomming_connection is in use
    //Consider palcing while(signal) here
	}
}

void ServerThread::SetRequest(quint8 type, QTcpSocket* connection)
{	
	switch (type)
	{
	case (quint8)ClientRequest::REGISTER: 
		request_ = new NewUserRequest(data_, &dal_, connection); 
		break;
	case (quint8)ClientRequest::LOGIN:
		qDebug() << "loginrequest";
          request_ = new LoginRequest(data_, &dal_, connection);

	}
}


ServerThread::~ServerThread()
{
	delete request_;
}
