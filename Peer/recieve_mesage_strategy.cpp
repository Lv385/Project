#include "recieve_mesage_strategy.h"
#include "signalredirector.h"

RecieveMessageStrategy::RecieveMessageStrategy()
    : AbstractStrategy(){
  redirector_.ConnectToMessageRecieved(this);
}

RecieveMessageStrategy::~RecieveMessageStrategy()
{

}

void RecieveMessageStrategy::DoWork() {
  cache_data_.SetMessage(peer_info_.id, message_.message);
  unsigned id = peer_info_.id;
  message_ = Parser::ParseAsMessage(data_);
  client_data_.AddMessageToDB(message_.message, id, id);
  emit MessageRecieved(id);
}
