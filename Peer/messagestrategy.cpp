#include "messagestrategy.h"

MessageStrategy::MessageStrategy(QObject *parent, PeerInfo peer_info,
                                 QTcpSocket* socket)
    : AbstractStrategy(peer_info) {
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
 //ocket_->write(to_write);
  timer_.start(kMsecConnectionDuration_);
}
