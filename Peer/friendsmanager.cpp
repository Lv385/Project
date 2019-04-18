#include "friendsmanager.h"

FriendsManager::FriendsManager(ApplicationInfo& info) 
    : app_info(info), 
      logger_(ClientLogger::Instance()){

}

FriendsManager::~FriendsManager() { 
  CleanUp();
}

void FriendsManager::SendMessages(const unsigned& id) { 
  if (pending_messages_[id].size() != 0)
  {
    Friend friend_info = client_data_.GetFriend(id);
    QString log = QString::number(id) + friend_info.login + " " + friend_info.ip +
                  " " + QString::number(friend_info.port);
  
    if(connecting_workers_.find(id) != connecting_workers_.end()) {
      logger_->WriteLog(INFO, "Still connecting to " + log);
    } else if(workers_.find(id) == workers_.end()) {
      logger_->WriteLog(INFO, "Connecting to " + log);
      Worker* worker = new Worker(friend_info, app_info.my_id);  // TOFIX
      connecting_workers_.insert(id, worker);
      connect(worker, SIGNAL(Connected(unsigned)), this,
              SLOT(OnConnected(unsigned)));
      connect(worker, SIGNAL(Disconnected(unsigned)), this,
              SLOT(OnDisconnected(unsigned)));
      connect(worker, SIGNAL(Error(unsigned)), this, SLOT(OnError(unsigned)));
      worker->dumpObjectInfo();
    } else {
      logger_->WriteLog(INFO, "Sending  to " + log);
      ReallySendMessages(id);
    }
  }
}

void FriendsManager::AddMessageToSend(unsigned id, QString message) {
  pending_messages_[id].append(message);
}

void FriendsManager::CleanUp() {
  for (auto a : workers_) a->deleteLater();
  workers_.clear();
  for (auto a : connecting_workers_) a->deleteLater();
  connecting_workers_.clear();
}

void FriendsManager::ReallySendMessages(unsigned id) {
  while (pending_messages_[id].size()) {
    QString toSend = *pending_messages_[id].begin();
    workers_[id]->SendMessage(toSend);
    pending_messages_[id].pop_front();
  }
  emit MessagesSent(id);
}

void FriendsManager::OnConnected(unsigned id) {
  workers_.insert(id, connecting_workers_[id]);
  connecting_workers_.remove(id);

  ReallySendMessages(id);
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

void FriendsManager::OnDisconnected(unsigned id) {
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
    worker->dumpObjectInfo();
  } 
}

