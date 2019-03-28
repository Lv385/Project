#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "abstractstrategy.h"
#include "login_response_strategy.h"
#include "register_response_strategy.h"
#include "friend_update_strategy.h"
#include "blockreader.h"
#include "messagestrategy.h"
#include "blockwriter.h"
#include "../Parser&Structs/request_types.h"
#include <QObject>
#include <memory>

class ServerManager : public QObject {
  Q_OBJECT

 public:
  ServerManager(QTcpSocket* socket);
  ServerManager();
  ~ServerManager();

 /* void Login();
  void Register();
  void AddFriend();*/
  void SendRequest(QByteArray data);

 private slots:
  void DoWork();
  void OnReadyReadBlock();

 private:
  AbstractStrategy* strategy_;
  QHash<quint8, AbstractStrategy*> strategies_;
  BlockWriter* writer_;
  BlockReader* reader_;
  QTcpSocket* socket_;
};

#endif  // !SERVERMANAGER_H
