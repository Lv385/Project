#ifndef WORKER_H
#define WORKER_H

#include "abstractstrategy.h"
#include "recieve_mesage_strategy.h"

#include "blockreader.h"
#include "messagestrategy.h"

#include <QByteArray>
#include <QObject>

#include "../Parser&Structs/parser.h"

class Worker : public QObject {
  Q_OBJECT

 public:
  Worker(BlockReader* reader, unsigned user_id);
  Worker(PeerInfo peer_info, QString message);
  ~Worker();
  void DoWork();
  void SetStrategy(StrategyType strategy_type);
  void set_message(QString message);

 signals:
  void Disconnected(unsigned id);
  void Connected(unsigned id);
  void MessageSent(unsigned id, bool result);

 public slots:
  void SendMessage();

 private slots:
  void OnDisconnected();
  void OnConnected();
  void OnReadyReadBlock();

 private:
  unsigned user_id_;
  AbstractStrategy* strategy_;
  PeerInfo peer_info_;
  QString message_;
  QTcpSocket* socket_;
  BlockReader* reader_;
  BlockWriter* writer_;
  QHash<quint8, AbstractStrategy*> strategies_;
  SignalRedirector& redirector_;
};

#endif  // !WORKER_H
