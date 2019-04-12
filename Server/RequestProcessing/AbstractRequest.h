#pragma once
#include <QObject>
#include <QTcpSocket>
#include <string>
#include  <time.h>
#include <QByteArray>
#include <QTcpSocket>
#include "../DAL/dal.h"
#include "../Logger/logger.h"
#include "../Parser&Structs/parser.h"
#include "../Parser&Structs/request_types.h"

// using namespace std;

class AbstractRequest : public QObject {
  Q_OBJECT
 public:
  AbstractRequest(DAL*, QTcpSocket*);
  // Receives socket initalized by client.
  // That sockets will be used to send correct responses.
  // Also that function may initialize outcome connection
  virtual bool SendResponde() = 0;

 protected:
  // every derived class will override this function in order to return
  // appropriate response according to incoming request. That response will be
  // stored in
  // string fields and will be processed but sendResponde()
  virtual void PrepareResponse() = 0;

  DAL* database_;
  QTcpSocket* client_socket_;
 signals:

 public slots:
  virtual void connected();

  // void readyRead();
};
