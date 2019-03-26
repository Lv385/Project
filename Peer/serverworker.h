#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include "abstractstrategy.h"
#include "messagestrategy.h"

#include <QObject>
#include <memory>

class ServerWorker : public QObject {
  Q_OBJECT

 public:
  ServerWorker(QObject* parent);
  ~ServerWorker();

 private:

  QTcpSocket* socket_;
};

#endif // !SERVERWORKER_H
