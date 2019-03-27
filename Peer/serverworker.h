#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include "abstractstrategy.h"
#include "messagestrategy.h"
#include "blockreader.h"
#include <QObject>
#include <memory>

class ServerWorker : public QObject {
  Q_OBJECT

 public:
  ServerWorker(QObject* parent);
  ~ServerWorker();
  void SetSocket(QTcpSocket* socket);

 private:
  BlockReader* reader_;
};

#endif  // !SERVERWORKER_H
