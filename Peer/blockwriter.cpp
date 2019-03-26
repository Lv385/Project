#include "blockwriter.h"

BlockWriter::BlockWriter(QObject* parent, QTcpSocket* socket)
    : QObject(parent),
      socket_(socket),
      unpossible_sequence_(Parser::GetUnpossibleSequence()){

}

BlockWriter::~BlockWriter(){}

void BlockWriter::WriteBlock(QByteArray data) {  
  socket_->write(data.append(unpossible_sequence_));
  //
}
