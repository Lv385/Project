#ifndef TEST_H
#define TEST_H

#include <QMessageBox>
#include <QNetworkSession>
#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include<ui_mainwindow.h>


class Peer : public QObject
{
     Q_OBJECT

public:
    explicit Peer(QObject *parent = nullptr);

    void sendMessage(QString message);

    QTcpServer* get_receiver_server() const {return m_receiver_server;}
    QString get_my_IP() const {return m_my_IP;}
    void set_receiver_IP(const QString &receiver_IP);
    void set_receiver_port(const QString &receiver_port);

signals:
    void sendMessageToUI(QString);


private slots:
    void setReceiverSocket();
    void readMessage(); // doesn't work
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QTcpServer* m_receiver_server = nullptr;
    QTcpSocket* m_sender_socket = nullptr;
    QTcpSocket* m_receiver_socket = nullptr;
    //QNetworkSession *networkSession = nullptr;

    QString m_my_IP;
    QString m_receiver_IP;
    QString m_receiver_port;

    QString m_received_message;

    QDataStream in; // not working


};

#endif // TEST_H
