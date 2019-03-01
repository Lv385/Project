#include "tcpserver.h"
#include "connection.h"

TcpServer::TcpServer(QObject *parent)
	: QTcpServer(parent)
{
<<<<<<< HEAD
	listen(QHostAddress::Any, 8989);
=======
	listen(QHostAddress::Any);
>>>>>>> 4aabedb... added server and connection
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
	Connection *connection = new Connection(socketDescriptor, this);
	emit NewConnection(connection);
}

TcpServer::~TcpServer()
{
}
