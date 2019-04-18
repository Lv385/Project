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
  FriendRequest request{info_.requester_login, RequestForMe};
  if(client_data_.Exist(request)){
  client_data_.SaveRequest(request);
  emit AddFriendRequestInfo(info_.requester_login);
  }
}
