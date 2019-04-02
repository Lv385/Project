#include "messagestrategy.h"

SendMessageStrategy::SendMessageStrategy(Friend peer_info,
                                 QTcpSocket* socket, QByteArray data)
    : AbstractStrategy(data), 
      writer_(socket){

}

SendMessageStrategy::~SendMessageStrategy() {}

void SendMessageStrategy::SendMessage() {
  MessageInfo mes = Parser::ParseAsMessage(data_);
//  QByteArray to_write = Parser::Message_ToByteArray();
 //ocket_->write(to_write);
  //timer_.start(kMsecConnectionDuration_);
}
