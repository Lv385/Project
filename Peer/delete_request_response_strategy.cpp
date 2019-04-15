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

  if (type == static_cast<quint8>(ServerRequest::DELETE_REQUEST_SUCCEED)) {
    emit DeleteRequestResult(true);
  }
  if (type == static_cast<quint8>(ServerRequest::DELETE_REQUEST_FAILED)) {
    emit DeleteRequestResult(false);
  }
}
