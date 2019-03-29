#include "friendsmanager.h"

FriendsManager::FriendsManager(ApplicationInfo& info) 
    : app_info(info) {

}


FriendsManager::~FriendsManager() {}

void FriendsManager::SendMessage(PeerInfo peer_info, QString message) { 
  unsigned id = peer_info.id;
  if (workers_.find(id) == workers_.end()) {
    Worker* worker = new Worker(peer_info, message);
    worker->set_my_id(app_info.my_id);
    connecting_workers_.insert(id, worker);
    connect(worker, SIGNAL(Connected(unsigned)), this, SLOT(OnConnected(unsigned)));
  } else {
    workers_[id]->set_my_id(app_info.my_id);
    workers_[id]->set_message(message);
    workers_[id]->SendMessage();
  }    
}

void FriendsManager::RemoveWorker(unsigned id) {
  delete workers_.find(id).value();
  workers_.remove(id);
}


void FriendsManager::OnConnected(unsigned id) { 
  workers_.insert(id, connecting_workers_[id]);
  connecting_workers_.remove(id);

}




void FriendsManager::OnFirstRequestRecieved() {
  BlockReader* reader = qobject_cast<BlockReader*>(sender());
  QByteArray data = reader->ReadNextBlock();

  if (Parser::getRequestType(data) ==
      static_cast<quint8>(ClientClientRequest::CONNECT)) {
    ConnectInfo connect_info = Parser::ParseAsConnectInfo(data);

    Worker* worker = new Worker(reader, connect_info.id);
    workers_.insert(connect_info.id, worker);
    connect(worker, SIGNAL(Disconnected(unsigned id)), this,
            SLOT(RemoveWorker(unsigned id)));
  } else {
    throw 1;
  }
}

// void ClientWorker::OnFirstRequest() {
//  QByteArray received_data, nextData;
//  int separatorIndex;
//  QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
//
//  received_data.append(socket->readAll());
//
//  // work on all requests if there are more than one
//  //  such a separator, untill we design something better
//  if (received_data.contains(Parser::GetUnpossibleSequence())) {
//    separatorIndex = received_data.indexOf(Parser::GetUnpossibleSequence());
//
//    nextData = received_data.mid(separatorIndex + 2);
//    received_data = received_data.left(separatorIndex);
//  }
//
//  Message mes = Parser::ParseAsMessage(received_data);
//
//  connections_[mes.id];
//}
