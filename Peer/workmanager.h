#ifndef WORKMANAGER_H
#define WORKMANAGER_H

#include <QHash>
#include <QObject>
#include <QSet>
#include <QTcpServer>
#include <QTcpSocket>

#include "abstractstrategy.h"
#include "clientworker.h"
#include "localserver.h"
#include "peerinfo.h"
#include "serverworker.h"
#include "workhelper.h"

class WorkManager : public QObject {
  Q_OBJECT

 public:
  WorkManager(QObject* parent);
  ~WorkManager();

  void SetWork(quint8 request_type, PeerInfo* peer_info, QByteArray* data,
               QTcpSocket* socket);

 private slots:
  void OnNewClientConnection(QTcpSocket* socket);
  void OnNewServerConnection(QTcpSocket* socket);

 private:
  LocalServer* local_server_;

  ClientWorker client_worker_;
  ServerWorker server_worker_;

  QSet<AbstractStrategy*> server_works_;
};

#endif  // !WORKMANAGER_H
