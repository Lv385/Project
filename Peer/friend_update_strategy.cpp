#include "friend_update_strategy.h"
#include "signalredirector.h"

FriendUpdateStrategy::FriendUpdateStrategy()
: AbstractStrategy(){
  redirector_.ConnectToStatusChanged(this);
}

FriendUpdateStrategy::~FriendUpdateStrategy()
{}

void FriendUpdateStrategy::DoWork() {
  info_ = Parser::ParseAsFriendUpdateInfo(data_);
  emit StatusChanged(info_.id, true);
  client_data_.UpdateIPPort(info_.id, info_.ip.toString(), info_.port);

}
