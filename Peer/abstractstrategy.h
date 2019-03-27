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
  virtual void DoWork() = 0;
  virtual ~AbstractStrategy();

 protected:
  QByteArray data_;
  DALManager dal;
  SignalRedirector& redirector_;
};

#endif  // !ABSTRACTSTRATEGY_H
