#ifndef TEST_H
#define TEST_H

#include <QMessageBox>
#include <QNetworkSession>
#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include<ui_mainwindow.h>
#include <QDebug>


class Peer : public QObject
{
     Q_OBJECT

public:
    explicit Peer(QObject *parent = nullptr);

    void SendMessage(QString message);

    quint16		 get_my_port() const {return receiver_server_->serverPort();}
    QHostAddress get_my_ip()   const {return my_ip_;}
    void set_receiver_ip  (const QString &receiver_IP);
    void set_receiver_port(const QString &receiver_port);

signals:
    void SendMessageToUI(QString);

private slots:
    void SetReceiverSocket();
    void ReadMessage(); // doesn't work
    void DisplayError(QAbstractSocket::SocketError socketError);

private:
    QTcpServer* receiver_server_ = nullptr;
    QTcpSocket* sender_socket_ = nullptr;
    QTcpSocket* receiver_socket_ = nullptr;
    //QNetworkSession *networkSession = nullptr;

	QHostAddress my_ip_;
    QString receiver_ip_;
    QString receiver_port_;

    QString received_message_;

    QDataStream in_; // not working
};

#endif // TEST_H
