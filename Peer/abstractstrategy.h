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
  AbstractStrategy();
  AbstractStrategy(QByteArray data);
  void set_data(QByteArray data);
  void set_peer_info(PeerInfo info);
  virtual void DoWork() = 0;
  virtual ~AbstractStrategy();

 protected:
  PeerInfo peer_info_;
  QByteArray data_;
  DALManager dal_;
  SignalRedirector& redirector_;
};

#endif  // !ABSTRACTSTRATEGY_H
