#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "application_info.h"

class Connection;

class LocalServer : public QTcpServer {
  Q_OBJECT

 public:
  LocalServer(ApplicationInfo& app_info);
  ~LocalServer();

  bool Start();

 signals:
  void NewConnection(QTcpSocket* socket);

 protected:
  void incomingConnection(qintptr socketDescriptor) override;

 private:
  ApplicationInfo& app_info_;
};

#endif