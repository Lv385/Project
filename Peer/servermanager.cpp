#include "servermanager.h"

ServerManager::ServerManager(QTcpSocket *socket) : socket_(socket) {
  reader_ = new BlockReader(socket_);
  writer_ = new BlockWriter(socket_);
  connect(reader_, SIGNAL(ReadyReadBlock()), this, SLOT(OnReadyReadBlock()));
}

ServerManager::ServerManager() {}

ServerManager::~ServerManager() {}

void ServerManager::OnReadyReadBlock() { 
  QByteArray data; 
  while (reader_->HasPendingBlock())
  {
    data = reader_->ReadNextBlock();
    quint8 type = Parser::getRequestType(data);
//    strategies_[type].set_data(data);

  }

}

