#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "application_info.h"
#include "clientlogger.h"
#include <QTcpServer>
#include <QTcpSocket>

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