#ifndef TEST_H
#define TEST_H

#include <QMessageBox>
#include <QNetworkSession>
#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QVector>
#include <QHostAddress>

#include <../DAL/Client/clientdb.h>
#include <ui_mainwindow.h>

#include "tcpserver.h"
#include "connection.h"

#include "../Parser&Structs/parser.h"


class Peer : public QObject	
{
     Q_OBJECT

public:
    explicit Peer(QObject *parent = nullptr, quint16 listen_port = 0);

	void SendRequest(unsigned id, QString message); //send message if there is connection, if not try to connect first

	quint16		 get_my_port() const { return tcp_server_->serverPort(); }
    QHostAddress get_my_ip()   const { return my_ip_; }

	void set_receiver_ip  (const QHostAddress &receiver_ip)   { receiver_ip_   = receiver_ip; }
	void set_receiver_port(const quint16	  &receiver_port) { receiver_port_ = receiver_port; }
	void set_login(QString login);
	bool is_active();

	bool startListening(quint16 listen_port);

	bool ConnectToPeer(unsigned id);

	bool LogIn(QString login, QString password);

signals:
	void SendLog(QString);
    void SendMessageToUI(QString);
	

private slots:
    void SetSocket(Connection *connection);		// setting 
	void OnServerConnected(Connection *connection); // 

    void ReadMessage();		//doesn't work
    void DisplayError(QAbstractSocket::SocketError socketError);

	void nullTcpSocket(); 

private:
    TcpServer* tcp_server_; //server for listening

	QString my_login_;
	QHostAddress server_ip_;
	quint16 server_port_;

	Connection *server_connection_; 
	QHash<unsigned, Connection*> connections_;
    //QNetworkSession *networkSession = nullptr;

	QHostAddress my_ip_;
	quint16 my_listen_port_;

	QHostAddress receiver_ip_;
    quint16 receiver_port_;

	bool is_active_;
	//QByteArray received_message_;

	//QDataStream in_; // not working
};

#endif // TEST_H
