#pragma once
#include <QTcpServer>
#include "DAL/dal.h"
#include "../Encryption/speck_cypher.h"

class AsyncServer : public QTcpServer {
  Q_OBJECT
 public:
  AsyncServer(QObject *parent = 0);
  ~AsyncServer();

 protected:
  void incomingConnection(qintptr socket_descriptor) override;

 private:
  static const short int PORT = 8888;
  // DAL dal_;
};
