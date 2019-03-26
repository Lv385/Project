#ifndef CLIENTWORKER_H
#define CLIENTWORKER_H

#include "abstractstrategy.h"
#include "peerinfo.h"
#include "messagestrategy.h"
#include "../Parser&Structs/parser.h"
#include "worker.h"

#include <QByteArray>
#include <QObject>
#include <QSet>
#include <QTcpSocket>
#include <QList>

class ClientWorker : public QObject {
  Q_OBJECT

public:
  ClientWorker(QObject *parent);
  ~ClientWorker();
  void SendRequest(PeerInfo peer_info, quint8 reques_type, QByteArray data);
 
private slots:
  void OnFirstRequest();
  void OnRequestRecieved();

private:
  QList<QTcpSocket *> undefined_connections;
  QHash<unsigned, AbstractStrategy*> connections_;
  QSet<AbstractStrategy *> works_;
};

#endif  // !CLIENTWORKER_H
