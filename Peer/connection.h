#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QHostAddress>

#include <ui_mainwindow.h>

#include "../Parser&Structs/parser.h"
#include "abstractstrategy.h"
#include "peerchattingstrategy.h"

class Connection : public QTcpSocket
{
	Q_OBJECT

public:
	Connection(QObject *parent);
	Connection(qintptr socketDescriptor, QObject *parent = 0);

	void SendMessage(QString message);
	void SetStrategy(quint8  StrategyType);

	~Connection();

private slots:		
	void TryReadLine();		

signals:
	void SendLog(QString);
	void SendMessageToUI(QString);
	

private:
	QByteArray received_data_;

	const QByteArray k_unpossiblle_2_bytes_sequence_;

	//AbstractStrategy strategy_;
};
#endif