#ifndef WORKER_H
#define WORKER_H

#include "abstractstrategy.h"
#include "blockreader.h"

#include <QObject>
#include <QByteArray>

class Worker : public QObject {
  Q_OBJECT

 public:
  Worker(QObject *parent);

  ~Worker();

 private:
  AbstractStrategy* strategy_;
  QByteArray data_;
 // BlockReader reader;
};

#endif  // !WORKER_H
