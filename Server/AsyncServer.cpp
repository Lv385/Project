#include "AsyncServer.h"
#include "ServerThread.h"
#include <QNetworkInterface>
#include <QUuid>
#include <string>

//Registration reg;
//reg.port = 5896;
//reg.login = QString("man");
//reg.password = QString("password");
//QByteArray ta = Parser::RegisterInfo_ToByteArray(reg);
//Registration atas = Parser::ParseAsRegisterInfo(ta);
//qDebug() << QString(atas.login) << atas.password << atas.port << "\n";

AsyncServer::AsyncServer(QObject *parent) :QTcpServer ()
{
	if (!this->listen(QHostAddress::Any, AsyncServer::PORT)) {
		qDebug() << "Failed to run server";
	}
	else {
		//get current ip
		QString ipAddress;
		QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
		// use the first non-localhost IPv4 address
		for (int i = 0; i < ipAddressesList.size(); ++i) {
			if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
				ipAddressesList.at(i).toIPv4Address()) {
				ipAddress = ipAddressesList.at(i).toString();
				break;
			}
		}
		// if we did not find one, use IPv4 localhost
		if (ipAddress.isEmpty())
			ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

		qDebug() << "Server are listening: " << ipAddress << ":" << this->serverPort();
	}      
	
}


AsyncServer::~AsyncServer()
{
}

void AsyncServer::incomingConnection(qintptr socketDescriptor)
{	
	ServerThread * newThread = new ServerThread(socketDescriptor, this);
	connect(newThread, SIGNAL(finished()), newThread, SLOT(deleteLater())); // delete ServerThread obj on thread completion
	newThread->start();
}
