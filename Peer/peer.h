#ifndef TEST_H
#define TEST_H

#include <QMessageBox>
#include <QNetworkSession>
#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <ui_mainwindow.h>
#include <QDebug>

class Peer : public QObject
{
     Q_OBJECT

public:
    explicit Peer(QObject *parent = nullptr);

	void SendMessage(QString message); //send message if there is connection, if not try to connect first

	quint16		 get_my_port() const { return tcp_server_->serverPort(); }
    QHostAddress get_my_ip()   const { return my_ip_;}

	void set_receiver_ip  (const QHostAddress &receiver_ip)   { receiver_ip_   = receiver_ip; }
	void set_receiver_port(const quint16	  &receiver_port) { receiver_port_ = receiver_port; }

	bool ConnectToPeer(QHostAddress receiver_ip, quint16 port); 

signals:
    void SendMessageToUI(QString);
	void SendLog(QString);

private slots:
    void SetSocket();		//setting 
    void ReadMessage();		//doesn't work
    void DisplayError(QAbstractSocket::SocketError socketError);
	void TryReadLine();		//read if \n is occured
	void nullTcpSocket(); 

private:
    QTcpServer* tcp_server_; //server for listening
	QTcpSocket* tcp_socket_; //socket for reading and writing to another peer(only for one peer at time)

    //QNetworkSession *networkSession = nullptr;

	QHostAddress my_ip_;

	QHostAddress receiver_ip_;
    quint16 receiver_port_;
	QByteArray received_message_;
    //QString received_message_;

	//QDataStream in_; // not working
};

#endif // TEST_H
