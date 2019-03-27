#include "worker.h"

Worker::Worker(BlockReader* reader) {
  connect(reader_, SIGNAL(ReadyReadBlock()), this, SLOT(OnReadyReadBlock()));

  //strategies_.insert(SEND_MESSAGE, new MessageStrategy(this, peer_info_));
  //strategies_.insert(RECEIVE_MESSAGE, new MessageStrategy(this, peer_info_));
  //strategies_.insert(SEND_MESSAGE, new MessageStrategy(this, peer_info_));
}

void Worker::DoWork() { 
  strategy_->DoWork();
}
 
void Worker::SetStrategy(StrategyType strategy_type) {
  strategy_ = strategies_[strategy_type];
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

void Worker::OnDisconnected() { 
  emit Disconnected(peer_info_.id); 
}

Worker::~Worker() {}
