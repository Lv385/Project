#include "connection.h"

Connection::Connection(QObject *parent)
	: QTcpSocket(parent)
{
}

Connection::Connection(qintptr socketDescriptor, QObject * parent)
{
	setSocketDescriptor(socketDescriptor);
}

Connection::~Connection()
{
}
