#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
<<<<<<< HEAD
#include <QHostAddress>

#include <ui_mainwindow.h>

=======
>>>>>>> 4aabedb... added server and connection

class Connection : public QTcpSocket
{
	Q_OBJECT

public:
	Connection(QObject *parent);
	Connection(qintptr socketDescriptor, QObject *parent = 0);

<<<<<<< HEAD
	void SendMessage(QString message);

	~Connection();

private slots:		
	void TryReadLine();		

signals:
	void SendLog(QString);
	void SendMessageToUI(QString);
private:
	QByteArray received_message_;
=======
	~Connection();
>>>>>>> 4aabedb... added server and connection
};
#endif