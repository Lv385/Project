#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "../Parser&Structs/request_types.h"
#include "abstractstrategy.h"
#include "blockreader.h"
#include "blockwriter.h"
#include "clientlogger.h"
#include "friend_update_strategy.h"
#include "login_response_strategy.h"
#include "messagestrategy.h"
#include "register_response_strategy.h"
#include "application_info.h"
#include <QObject>
#include <memory>
#
class ServerManager : public QObject {
  Q_OBJECT

 public:
  ServerManager(QTcpSocket* socket, ApplicationInfo& info);
  ServerManager();
  ~ServerManager();
  void set_socket(QTcpSocket* socket);
  void SendRequest(QByteArray data);

 private slots:
  void DoWork();
  void OnReadyReadBlock();
  void OnConnected();

 private:
  QByteArray data_;
  ApplicationInfo& app_info_;
  AbstractStrategy* strategy_;
  QHash<quint8, AbstractStrategy*> strategies_;
  BlockWriter* writer_;
  BlockReader* reader_;
  QTcpSocket* socket_;
  ClientLogger* logger_;
};

#endif  // !SERVERMANAGER_H
