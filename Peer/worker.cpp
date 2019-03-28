#include "worker.h"

Worker::Worker(BlockReader* reader)
    : reader_(reader), 
      socket_(reader_->get_socket()){
  connect(reader_, SIGNAL(ReadyReadBlock()), this, SLOT(OnReadyReadBlock()));

  writer_ = new BlockWriter(socket_);
  //strategies_.insert(SEND_MESSAGE, new MessageStrategy(this, peer_info_));
  //strategies_.insert(RECEIVE_MESSAGE, new MessageStrategy(this, peer_info_));
  //strategies_.insert(SEND_MESSAGE, new MessageStrategy(this, peer_info_));
}


Worker::Worker(PeerInfo peer_info, QString message) { 
  QTcpSocket* socket = new QTcpSocket();
}

void Worker::DoWork() { 
  strategy_->DoWork();
}
 
void Worker::SetStrategy(StrategyType strategy_type) {
  strategy_ = strategies_[strategy_type];
}

void Worker::SendMessage() {
  Message mes = {message_};
  QByteArray data = Parser::Message_ToByteArray(mes);
  writer_->WriteBlock(data);
}

void Worker::OnDisconnected() {
  emit Disconnected(peer_info_.id);
}

void Worker::OnConnected() { 
  emit Connected(peer_info_.id);
}

void Worker::OnReadyReadBlock() {
  QByteArray data;
  while (reader_->HasPendingBlock()) {
    data = reader_->ReadNextBlock();
    quint8 type = Parser::getRequestType(data);
    switch (type) {
      case static_cast<quint8>(ClientClientRequest::MESSAGE): {
        SetStrategy(StrategyType::RECEIVE_MESSAGE);
        break;
      }
    }
    DoWork();
  }
}

Worker::~Worker() {}
