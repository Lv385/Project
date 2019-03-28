#include "servermanager.h"

ServerManager::ServerManager(QTcpSocket *socket) : socket_(socket) {
  reader_ = new BlockReader(socket_);
  writer_ = new BlockWriter(socket_);
  connect(reader_, SIGNAL(ReadyReadBlock()), this, SLOT(OnReadyReadBlock()));

  AbstractStrategy* login = new LoginResponseStrategy();
  AbstractStrategy* reg = new RegisterResponseStrategy();
  AbstractStrategy* friend_update = new FriendUpdateStrategy();

  strategies_.insert(static_cast<quint8>(ServerRequest::LOGIN_SUCCEED), login);
  strategies_.insert(static_cast<quint8>(ServerRequest::LOGIN_FAILED), login);
  strategies_.insert(static_cast<quint8>(ServerRequest::REGISTER_SUCCEED), reg);
  strategies_.insert(static_cast<quint8>(ServerRequest::REGISTER_FAILED), reg);
  strategies_.insert(static_cast<quint8>(ServerRequest::FRIEND_UPDATE_INFO), friend_update);
}

ServerManager::ServerManager() {
}

ServerManager::~ServerManager() {
}

void ServerManager::SendRequest(QByteArray data) { 
  writer_->WriteBlock(data); 
}

void ServerManager::DoWork() { 
  strategy_->DoWork(); 
}

void ServerManager::OnReadyReadBlock() { 
  QByteArray data; 
  while (reader_->HasPendingBlock())
  {
    data = reader_->ReadNextBlock();
    quint8 type = Parser::getRequestType(data);
    strategy_ = strategies_[type];
    strategy_->set_data(data);
    DoWork();
  }
}

