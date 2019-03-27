#ifndef ABSTRACTSTRATEGY_H
#define ABSTRACTSTRATEGY_H

#include "blockwriter.h"
#include "dalmanager.h"
#include "peerinfo.h"

#include <QByteArray>
#include <QObject>
#include <QTcpSocket>

#include "../Parser&Structs/parser.h"

class SignalRedirector;

enum StrategyType : quint8 {
  SEND_MESSAGE,
  RECEIVE_MESSAGE,
  LOGIN,
  REGISTER,
  FIND_FRIEND,
  ADD_FRIEND
};

class AbstractStrategy : public QObject {
  Q_OBJECT

 public:
  AbstractStrategy(PeerInfo peer_info);
  virtual void DoWork() = 0;
  virtual ~AbstractStrategy();

 public slots:
  // virtual void DoWork() = 0;

 protected:
  PeerInfo peer_info_;
  DALManager cdb_;
  QByteArray data_;
  SignalRedirector& redirector_;
};

#endif  // !ABSTRACTSTRATEGY_H
