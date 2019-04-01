#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "../Parser&Structs/parser.h"
#include "abstractstrategy.h"
#include "messagestrategy.h"
#include "peerinfo.h"
#include "worker.h"
#include "application_info.h"
#include "clientlogger.h"

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QSet>
#include <QTcpSocket>

class FriendsManager : public QObject {
  Q_OBJECT

 public:
  FriendsManager(ApplicationInfo& info);
  ~FriendsManager();
  void SendMessage(PeerInfo peer_info, QString message);

 private slots:
  void OnFirstRequestRecieved();

  void OnDisconnected(unsigned id);
  void OnConnected(unsigned id);
  void OnError(unsigned id);

 private:
  ApplicationInfo& app_info;
  QHash<unsigned, Worker*> connecting_workers_;
  QHash<unsigned, Worker*> workers_;
  ClientLogger* logger_;
};

#endif  // !CLIENTMANAGER_H
