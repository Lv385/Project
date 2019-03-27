#ifndef CLIENTWORKER_H
#define CLIENTWORKER_H

#include "../Parser&Structs/parser.h"
#include "abstractstrategy.h"
#include "messagestrategy.h"
#include "peerinfo.h"
#include "worker.h"

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QSet>
#include <QTcpSocket>

class ClientWorker : public QObject {
  Q_OBJECT

 public:
  ClientWorker(QObject *parent);
  ~ClientWorker();
  void SendRequest(PeerInfo peer_info, quint8 reques_type, QByteArray data);

 private slots:
  void OnFirstRequestRecieved();
  void RemoveWorker(unsigned id);

 private:
  QList<QTcpSocket *> undefined_connections;
  QHash<unsigned, Worker *> workers_;
  QSet<AbstractStrategy *> works_;
};

#endif  // !CLIENTWORKER_H
