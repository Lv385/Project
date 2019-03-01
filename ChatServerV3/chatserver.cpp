#include "chatserver.h"

#include <QDataStream>
#include <QNetworkInterface>

ChatServer::ChatServer(QObject *parent) : QObject(parent)
{
	//ServerDB db;
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any,ChatServer::PORT)){
        qDebug()<<"Failed to run server";
    }else{
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


        qDebug()<<"Server are listening: "<<ipAddress<<":"<<server->serverPort();
    }
}

void ChatServer::newConnection(){
    while(server->hasPendingConnections()){
        QTcpSocket* socket= server->nextPendingConnection();
        connect(socket, &QAbstractSocket::disconnected,
                socket, &QObject::deleteLater);
        qDebug()<<"Client "<<socket->peerAddress()<<" : "<<socket ->peerPort();

        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();

        // get the data

        QString clientInput(socket->readAll());
        qDebug() <<clientInput ;

        //Responde to client

        socket->write("Hello");
        socket->disconnectFromHost();
    }
}

