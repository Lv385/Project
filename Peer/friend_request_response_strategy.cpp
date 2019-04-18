#include "friend_request_response_strategy.h"
#include "signalredirector.h"

FriendRequestResponseStrategy::FriendRequestResponseStrategy()
    : AbstractStrategy() {
  redirector_.ConnectToFriendRequestResult(this);
}

FriendRequestResponseStrategy::~FriendRequestResponseStrategy()
{}

void FriendRequestResponseStrategy::DoWork() {
  ServerRequest type = static_cast<ServerRequest>(Parser::getRequestType(data_));

  if (type == ServerRequest::FRIEND_REQUEST_SUCCEED) {
    emit FriendRequestResult(true);
  }
  if (type == ServerRequest::FRIEND_REQUEST_FAILED) {
    emit FriendRequestResult(false);
  }
}
