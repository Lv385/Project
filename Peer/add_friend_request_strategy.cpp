#include "add_friend_request_strategy.h"
#include "signalredirector.h"

AddFriendRequestStrategy::AddFriendRequestStrategy()
    : AbstractStrategy(){
  redirector_.ConnectToAddFriendRequestInfo(this);
}

AddFriendRequestStrategy::~AddFriendRequestStrategy()
{}

void AddFriendRequestStrategy::DoWork() {
  info_ = Parser::ParseAsAddFriendInfo(data_);
  emit AddFriendRequestInfo(info_.requester_login);
}
