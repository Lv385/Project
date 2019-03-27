#include "workmanager.h"

WorkManager::WorkManager(QObject* parent)
    : QObject(parent), client_worker_(this), server_worker_(this) {}

WorkManager::~WorkManager() {
  connect(local_server_, SIGNAL(NewConnection(Connection*)),
                   this, SLOT(OnNewConnection(Connection*)));
  
}


void WorkManager::OnNewConnection(QTcpSocket* socket) {
  if (socket->peerAddress().isEqual(app_info_.remote_server_ip),
      QHostAddress::TolerantConversion) {
    server_worker_;
  } else {
    BlockReader* reader = new BlockReader(socket);
    connect(reader, SIGNAL(ReadyReadBlock()), 
   &client_worker_, SLOT(OnFirstRequestRecieved()));
  }
}

void WorkManager::SetWork(quint8 request_type, PeerInfo* peer_info,
                          QByteArray* data, QTcpSocket* socket) {
  switch (request_type) {
    case static_cast<quint8>(ClientClientRequest::MESSAGE): {
      // quint32 id = peer_info->id;
      // if (client_works_.find(id) == client_works_.end()) {
      //  AbstractStrategy* strategy =
      //      new MessageStrategy(nullptr, peer_info, data, 0);
      //  connect(strategy, SIGNAL(destroyed()), this, SLOT(RemoveWork()));
      //  client_works_[id] = strategy;
      //} else {
      //  client_works_[id]->DoWork();
      //}
      break;
    }
    case static_cast<quint8>(ClientRequest::LOGIN): {
    }
  }
}
