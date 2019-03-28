#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

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

class FriendsManager : public QObject {
  Q_OBJECT

 public:
  FriendsManager();
  ~FriendsManager();
  void SendMessage(PeerInfo peer_info, QString message);

 private slots:
  void OnFirstRequestRecieved();
  void RemoveWorker(unsigned id);
  void OnConnected();
  void OnError();

 private:
  QHash<unsigned, Worker*> connecting_sockets_;
  QHash<unsigned, Worker*> workers_;
  QSet<AbstractStrategy*> works_;
};

#endif  // !CLIENTMANAGER_H
