#ifndef WORKER_H
#define WORKER_H

#include "abstractstrategy.h"
#include "clientlogger.h"
#include "dataaccessor.h"
#include "recieve_mesage_strategy.h"

#include "blockreader.h"
#include "messagestrategy.h"

#include <QByteArray>
#include <QMap>
#include <QObject>
#include <QTimer>

#include "../Parser&Structs/parser.h"

class SignalRedirector;

class Worker : public QObject {
  Q_OBJECT

 public:
  Worker(BlockReader* reader, unsigned user_id, unsigned my_id);
  Worker(Friend peer_info, unsigned my_id);
  ~Worker();

  void DoWork();
  void SetStrategy(ClientClientRequest request);
  void set_message(QString message);
  void set_my_id(unsigned id);

 signals:
  void Disconnected(unsigned id);
  void Connected(unsigned id);
  void Error(unsigned id);
  void MessageSent(unsigned id, bool result);
  void MessageRecieved(Message* message);

 public slots:
  void SendMessage(const QString& message);

 private slots:
  void OnDisconnected();
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
  QMap<ClientClientRequest, AbstractStrategy*> strategies_;
  SignalRedirector& redirector_;
  ClientLogger* logger_;
  QTimer timer_;
  int k_msc = 20000;  // connection time
};

#endif  // !WORKER_H
