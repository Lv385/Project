#ifndef WORKHELPER_H
#define WORKHELPER_H

 
#include "abstractstrategy.h"

#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
#include <memory>

#include "../Parser&Structs/parser.h"


class WorkHelper : public QObject {
  Q_OBJECT

 public:
  WorkHelper(QObject* parent, QTcpSocket* socket);
  ~WorkHelper();

 signals:
  void WorkDefined(quint8, Friend*, QByteArray*, QTcpSocket*);

 private slots:
  void OnReadyRead();
  AbstractStrategy* GetWork();

 private:
  std::shared_ptr<Friend> peer_info;
  QByteArray* data_;
  QTcpSocket* socket_;
  AbstractStrategy* work_;
  //#tofix will add reader/writer and use block
  const QByteArray k_unpossiblle_2_bytes_sequence_;
};

#endif  // !WORKHELPER_H
