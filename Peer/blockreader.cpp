#include "blockreader.h"

BlockReader::BlockReader(QObject* parent, QTcpSocket* socket)
    : QObject(parent),
      socket_(socket),
      unpossible_sequence_(Parser::GetUnpossibleSequence()) {
  connect(socket_, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
}

BlockReader::~BlockReader() {}

QByteArray BlockReader::ReadNextBlock() {
  QByteArray result;
  result = blocks_.first();
  blocks_.pop_front();
  return result;
}

bool BlockReader::HasPendingBlock() { 
  return blocks_.size() != 0;
}
void BlockReader::OnReadyRead() {
  int separatorIndex;

  while (socket_->bytesAvailable()) {
    data_.append(socket_->readAll());
    while (data_.contains(unpossible_sequence_)) {
      separatorIndex = data_.indexOf(unpossible_sequence_);

      blocks_.push_back(data_.left(separatorIndex));
      data_ = data_.mid(separatorIndex + 2);

      emit ReadyReadBlock();
    }
  }
}

