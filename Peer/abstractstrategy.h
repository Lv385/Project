#ifndef ABSTRACTSTRATEGY_H
#define ABSTRACTSTRATEGY_H

#include <QByteArray>
#include <QObject>
#include <QTcpSocket>

#include "../Parser&Structs/parser.h"
#include "dalmanager.h"
#include "peerinfo.h"

class AbstractStrategy : public QObject {
  Q_OBJECT

 public:
  AbstractStrategy(){};
  AbstractStrategy(QObject* parent, PeerInfo peer_info, QByteArray data,
                   QTcpSocket* socket = nullptr);

  virtual ~AbstractStrategy();

 public slots:
 // virtual void DoWork() = 0;

 protected:
  PeerInfo peer_info_;
  QTcpSocket socket_;
  DALManager cdb;
  QByteArray data_;

  const QByteArray k_unpossiblle_2_bytes_sequence_;  //#tofix
};

#endif  // !ABSTRACTSTRATEGY_H
