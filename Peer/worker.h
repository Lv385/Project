#ifndef WORKER_H
#define WORKER_H

#include "abstractstrategy.h"
#include "clientlogger.h"
#include "dataaccessor.h"
#include "recieve_mesage_strategy.h"

#include "blockreader.h"
#include "messagestrategy.h"

#include <QByteArray>
#include <QObject>
#include <QTimer>

#include "../Parser&Structs/parser.h"

class SignalRedirector;


class Worker : public QObject {
  Q_OBJECT

 public:
  Worker(BlockReader* reader, unsigned user_id, unsigned my_id);
  Worker(Friend peer_info, QString message, unsigned my_id);
  ~Worker();
  void DoWork();
  void SetStrategy(StrategyType strategy_type);
  void set_message(QString message);
  void set_my_id(unsigned id);

 signals:
  void Disconnected(unsigned id);
  void Connected(unsigned id);
  void Error(unsigned id);
  void MessageSent(unsigned id, bool result);
  void MessageRecieved(unsigned id);

 public slots:
  void SendMessage();

 private slots:
  void OnDisconnected();
  void OnTimedOut();
  void OnConnected();
  void OnError(QAbstractSocket::SocketError);
  void OnReadyReadBlock();

 private:
  unsigned my_id_;
  AbstractStrategy* strategy_;
  DataAccessor client_data_;
  Friend peer_info_;
  QString message_;
  QTcpSocket* socket_;
  BlockReader* reader_;
  BlockWriter* writer_;
  QHash<quint8, AbstractStrategy*> strategies_;
  SignalRedirector& redirector_;
  ClientLogger* logger_;
  QTimer timer_;
  int k_msc = 10000;  // connection time
};

#endif  // !WORKER_H
