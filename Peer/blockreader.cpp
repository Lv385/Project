#include "blockreader.h"

BlockReader::BlockReader(QTcpSocket* socket)
    : socket_(socket),
      unpossible_sequence_(Parser::GetUnpossibleSequence()) {
  connect(socket_, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
}

BlockReader::~BlockReader() {}

void BlockReader::set_socket(QTcpSocket* socket) { 
  if(socket_){
    disconnect(socket_, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
  }
  socket_ = socket; 
  connect(socket_, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
}

QTcpSocket* BlockReader::get_socket() { 
  return socket_;
}

QByteArray BlockReader::ReadNextBlock() {
  QByteArray result;
  result = blocks_.first();
  blocks_.pop_front();
  return result;
}

bool BlockReader::HasPendingBlock() { 
  return blocks_.size() != 0; }

bool BlockReader::WaitForReadyReadBlock() { 
  return false; 
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

