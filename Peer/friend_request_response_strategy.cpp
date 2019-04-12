#include "friend_request_response_strategy.h"
#include "signalredirector.h"

FriendRequestResponseStrategy::FriendRequestResponseStrategy()
    : AbstractStrategy() {
  redirector_.ConnectToFriendRequestResult(this);
  redirector_.ConnectToAddFriendRequestInfo(this);
}

FriendRequestResponseStrategy::~FriendRequestResponseStrategy()
{}

void FriendRequestResponseStrategy::DoWork() {
  quint8 type = Parser::getRequestType(data_);
  AddFriendInfo info = Parser::ParseAsAddFriendInfo(data_);

  if (type == static_cast<quint8>(ServerRequest::FRIEND_REQUEST_SUCCEED)) {
    emit FriendRequestResult(true);
  }
  if (type == static_cast<quint8>(ServerRequest::FRIEND_REQUEST_FAILED)) {
    emit FriendRequestResult(false);
  }
  if (type == static_cast<quint8>(ServerRequest::ADD_FRIEND_REQUEST)) {
    emit AddFriendRequestInfo(info.requester_login);
  }
}
