#include "blockwriter.h"

BlockWriter::BlockWriter(QTcpSocket* socket)
    : socket_(socket), 
      unpossible_sequence_(Parser::GetUnpossibleSequence()) {

}

BlockWriter::~BlockWriter(){}

void BlockWriter::WriteBlock(QByteArray data) {  
  socket_->write(data.append(unpossible_sequence_));
}

void BlockWriter::set_socket(QTcpSocket* socket) { 
  socket_ = socket;
}
