#include "tcpserver.h"
#include "connection.h"

TcpServer::TcpServer(QObject *parent)
	: QTcpServer(parent)
{
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
	Connection *connection = new Connection(socketDescriptor, this);
	emit NewConnection(connection);
}

TcpServer::~TcpServer()
{
}
