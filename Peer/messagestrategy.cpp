#include "messagestrategy.h"

MessageStrategy::MessageStrategy(QObject *parent, PeerInfo peer_info,
                                 QByteArray data, QTcpSocket* socket)
    : AbstractStrategy(parent
      , peer_info
      , data
      , socket) {
  timer_.setSingleShot(true);
  timer_.start(kMsecConnectionDuration_);
  connect(&timer_, SIGNAL(timeout()), this, SLOT(disconnectFromHost()));
  connect(this, SIGNAL(connected()), this, SLOT(SendMessage()));
  connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

MessageStrategy::~MessageStrategy() {}

void MessageStrategy::SendMessage() {
  Message mes = Parser::ParseAsMessage(data_);
  QByteArray to_write = Parser::Message_ToByteArray(mes);
  to_write.append(k_unpossiblle_2_bytes_sequence_);  // append separator
 //ocket_->write(to_write);
  timer_.start(kMsecConnectionDuration_);
}
