#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Connection : public QTcpSocket
{
	Q_OBJECT

public:
	Connection(QObject *parent);
	Connection(qintptr socketDescriptor, QObject *parent = 0);

	~Connection();
};
#endif