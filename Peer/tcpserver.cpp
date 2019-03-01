#include "tcpserver.h"
#include "connection.h"

TcpServer::TcpServer(QObject *parent)
	: QTcpServer(parent)
{
	listen(QHostAddress::Any, 8989);
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
	Connection *connection = new Connection(socketDescriptor, this);
	emit NewConnection(connection);
}

TcpServer::~TcpServer()
{
}
