#ifndef WORKMANAGER_H
#define WORKMANAGER_H

#include "abstractstrategy.h"
#include "clientworker.h"
#include "localserver.h"
#include "peerinfo.h"
#include "serverworker.h"
#include "workhelper.h"
#include "worker.h"
#include "applciation_info.h"

#include <QHash>
#include <QObject>
#include <QSet>
#include <QTcpServer>
#include <QTcpSocket>

class WorkManager : public QObject {
  Q_OBJECT

 public:
  WorkManager(QObject* parent);
  ~WorkManager();

  void SetWork(quint8 request_type, PeerInfo* peer_info, QByteArray* data,
               QTcpSocket* socket);

 private slots:
  void OnNewConnection(QTcpSocket* socket);

 private:

  LocalServer* local_server_;

  ClientWorker client_worker_;
  ServerWorker server_worker_;
  
  ApplicationInfo app_info_;

 // QSet<AbstractStrategy*> server_works_;
};

#endif  // !WORKMANAGER_H
