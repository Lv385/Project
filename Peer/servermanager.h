#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "abstractstrategy.h"
#include "blockreader.h"
#include "messagestrategy.h"
#include "blockwriter.h"
#include <QObject>
#include <memory>

class ServerManager : public QObject {
  Q_OBJECT

 public:
  ServerManager(QTcpSocket* socket);
  ServerManager();
  ~ServerManager();

  void Login();
  void Register();
  void AddFriend();

 private slots:
  void OnReadyReadBlock();

 private:
  AbstractStrategy* strategy_;
  QHash<StrategyType, AbstractStrategy*> strategies_;
  BlockWriter* writer_;
  BlockReader* reader_;
  QTcpSocket* socket_;
};

#endif  // !SERVERMANAGER_H
