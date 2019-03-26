#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class Connection;

class LocalServer : public QTcpServer {
  Q_OBJECT

 public:
  LocalServer(QObject* parent);
  ~LocalServer();
  void set_remote_server_ip_port(QHostAddress& remote_server_ip,
                             quint16& remote_server_port);
 signals:
  void NewClientConnection(QTcpSocket* socket);
  void NewServerConnection(QTcpSocket* socket);

 protected:
  void incomingConnection(qintptr socketDescriptor) override;

 private:
  QHostAddress remote_server_ip_;
  quint16 remote_server_port_;
};

#endif