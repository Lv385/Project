#include "delete_request_response_strategy.h"
#include "signalredirector.h"

DeleteRequestResponseStrategy::DeleteRequestResponseStrategy()
    : AbstractStrategy(){
  redirector_.ConnectToDeleteRequestResult(this);
}

DeleteRequestResponseStrategy::~DeleteRequestResponseStrategy()
{}

void DeleteRequestResponseStrategy::DoWork() {
  quint8 type = Parser::getRequestType(data_);
  DeleteNotificationInfo info = Parser::ParseAsDeleteNotificationInfo(data_);

  if (type == static_cast<quint8>(ServerRequest::DELETE_REQUEST_SUCCEED)) {
    client_data_.DeleteFriend(info.id);
    emit DeleteRequestResult(info.id);
  } else if (type == static_cast<quint8>(ServerRequest::DELETE_REQUEST_FAILED)) {
    emit DeleteRequestResult(0);
  } else if (type == static_cast<quint8>(ServerRequest::DELETE_NOTIFICATION_INFO)) {
    client_data_.DeleteFriend(info.id);
    emit DeleteRequestResult(info.id);
  }
}
