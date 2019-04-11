#include "recieve_mesage_strategy.h"
#include "signalredirector.h"

RecieveMessageStrategy::RecieveMessageStrategy()
    : AbstractStrategy() {
  redirector_.ConnectToMessageRecieved(this);
}

RecieveMessageStrategy::~RecieveMessageStrategy(){

}

void RecieveMessageStrategy::DoWork() {
  unsigned id = peer_info_.id;
  message_info_ = Parser::ParseAsMessage(data_);
  Message* message = new Message{0, id, id, message_info_.message, //no way to know message id:) #tofix
                      QDate::currentDate(), QTime::currentTime()};
  client_data_.AddMessageToDB(*message);
  emit MessageRecieved(message);
}
