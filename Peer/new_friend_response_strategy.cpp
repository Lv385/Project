#include "new_friend_response_strategy.h"
#include "signalredirector.h"

NewFriendResponseStrategy::NewFriendResponseStrategy() : AbstractStrategy() {
  redirector_.ConnectToNewFriendRequestResult(this);
}

NewFriendResponseStrategy::~NewFriendResponseStrategy() {}

void NewFriendResponseStrategy::DoWork() {
  info_ = Parser::ParseAsNewFriendInfo(data_);
  emit NewFriendRequestResult(info_.login, info_.id);
  client_data_.AddFriend(info_.id, info_.login, info_.ip.toString(),
                         info_.port);
}
