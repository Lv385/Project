#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QHostAddress>

#include <ui_mainwindow.h>


class Connection : public QTcpSocket
{
	Q_OBJECT

public:
	Connection(QObject *parent);
	Connection(qintptr socketDescriptor, QObject *parent = 0);

	void SendMessage(QString message);

	~Connection();

private slots:		
	void TryReadLine();		

signals:
	void SendLog(QString);
	void SendMessageToUI(QString);
private:
	QByteArray received_message_;
};
#endif