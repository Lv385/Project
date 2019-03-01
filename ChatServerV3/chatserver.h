#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <../DAL/Server/serverdb.h>

class ChatServer : public QObject
{
    Q_OBJECT
public:
    static const short int PORT = 8888;
    explicit ChatServer(QObject *parent = nullptr);
private:
    QTcpServer *server;


signals:

public slots:
    void newConnection();
    //void readyRead();

};

#endif // CHATSERVER_H
