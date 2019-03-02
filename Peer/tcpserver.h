#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class Connection;

class TcpServer : public QTcpServer
{
	Q_OBJECT

public:
	TcpServer(QObject *parent);
	~TcpServer();
signals:
	void NewConnection(Connection *connection);

protected:
	void incomingConnection(qintptr socketDescriptor) override;
	
};

#endif