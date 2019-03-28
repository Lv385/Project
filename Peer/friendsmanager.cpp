#include "friendsmanager.h"

FriendsManager::FriendsManager() {}

FriendsManager::~FriendsManager() {}

void FriendsManager::SendMessage(PeerInfo peer_info, QString message) { 
  unsigned id = peer_info.id;
  if (workers_.find(id) == workers_.end()) {
    Worker* worker = new Worker(peer_info, message);

  } else {
    workers_[id]->SendMessage();
  }    
}

//void FriendsManager::SendRequest(PeerInfo peer_info, quint8 request_type,
//                               QByteArray data) {
//  quint32 id = peer_info.id;
//
//  AbstractStrategy* strategy;
//
//  switch (request_type) {
//    case static_cast<quint8>(ClientClientRequest::MESSAGE): {
//      workers_[id];
//      break;
//    }
//    default: { throw 1; }
//  }
//  //  strategy->DoWork();
//  delete strategy;
//}

void FriendsManager::RemoveWorker(unsigned id) {
  delete workers_.find(id).value();
  workers_.remove(id);
}

void FriendsManager::OnConnected() {
}

void FriendsManager::OnError() {

}


void FriendsManager::OnFirstRequestRecieved() {
  BlockReader* reader = qobject_cast<BlockReader*>(sender());
  QByteArray data = reader->ReadNextBlock();

  if (Parser::getRequestType(data) ==
      static_cast<quint8>(ClientClientRequest::CONNECT)) {
    ConnectInfo connect_info = Parser::ParseAsConnectInfo(data);

    Worker* worker = new Worker(reader);
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
