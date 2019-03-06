#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class Connection;

class TcpServer : public QTcpServer
{
	Q_OBJECT

public:
	TcpServer(QObject *parent, QHostAddress remote_server_ip, quint16 remote_server_port);
	~TcpServer();
signals:
	void NewConnection(Connection* connection);
	void NewServerConnection(Connection* connection);

protected:
	void incomingConnection(qintptr socketDescriptor) override;
private:
	QHostAddress remote_server_ip_;
	quint16 remote_server_port_;	
};

#endif