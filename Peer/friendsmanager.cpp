#include "friendsmanager.h"

FriendsManager::FriendsManager(ApplicationInfo& info) 
    : app_info(info), 
      logger_(ClientLogger::Instance()){

}


FriendsManager::~FriendsManager() {}

void FriendsManager::SendMessage(Friend peer_info, QString message) { 
  unsigned id = peer_info.id;
  QString log = QString::number(id) + peer_info.login + 
" " + peer_info.ip + " " + QString::number(peer_info.port);
  
  if(connecting_workers_.find(id) != connecting_workers_.end()) {
    logger_->WriteLog(INFO, "Still connecting to " + log);

  } else if(workers_.find(id) == workers_.end()) {
    logger_->WriteLog(INFO, "Connecting to " + log);
    Worker* worker = new Worker(peer_info, message, app_info.my_id);
    connecting_workers_.insert(id, worker);
    connect(worker, SIGNAL(Connected(unsigned)), this,
            SLOT(OnConnected(unsigned)));
    connect(worker, SIGNAL(Disconnected(unsigned)), this,
            SLOT(OnDisconnected(unsigned)));
    connect(worker, SIGNAL(Error(unsigned)), this, SLOT(OnError(unsigned)));
  } else {
    logger_->WriteLog(INFO, "Sending  to " + log);
    workers_[id]->set_my_id(app_info.my_id);
    workers_[id]->set_message(message);
    workers_[id]->SendMessage();
  }
}


void FriendsManager::OnDisconnected(unsigned id) {
  if (workers_.find(id) != workers_.end()) {
    Worker* to_delete = workers_[id];
    workers_.remove(id);
    delete to_delete; 
  }
}

void FriendsManager::OnConnected(unsigned id) { 
  workers_.insert(id, connecting_workers_[id]);
  connecting_workers_.remove(id);
}

void FriendsManager::OnError(unsigned id) {
  logger_->WriteLog(ERROR, "Failed on to" + QString::number(id));

  if (connecting_workers_.find(id) != connecting_workers_.end()) {
    Worker* to_delete = connecting_workers_[id];
    connecting_workers_.remove(id);
    delete to_delete;
  }
  if (workers_.find(id) != workers_.end()) {
    Worker* to_delete = workers_[id];
    workers_.remove(id);
    delete to_delete;
  }
}

void FriendsManager::OnFirstRequestRecieved() {
  BlockReader* reader = qobject_cast<BlockReader*>(sender());
  QByteArray data = reader->ReadNextBlock();

  if (Parser::getRequestType(data) ==
      static_cast<quint8>(ClientClientRequest::CONNECT)) {
    ConnectInfo connect_info = Parser::ParseAsConnectInfo(data);

    Worker* worker = new Worker(reader, connect_info.id, app_info.my_id);
    workers_.insert(connect_info.id, worker);
    connect(worker, SIGNAL(Disconnected(unsigned id)), this,
            SLOT(OnDisconnected(unsigned id)));
    connect(worker, SIGNAL(Error(unsigned id)), this,
            SLOT(OnDisconnected(unsigned id)));
    disconnect(reader, SIGNAL(ReadyReadBlock()), this,
               SLOT(OnFirstRequestRecieved()));
  } 
}

