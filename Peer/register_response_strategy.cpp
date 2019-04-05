#include "register_response_strategy.h"
#include "signalredirector.h"

RegisterResponseStrategy::RegisterResponseStrategy() 
  : AbstractStrategy() {
  redirector_.ConnectToRegisterResult(this);
}


RegisterResponseStrategy::~RegisterResponseStrategy()
{}

void RegisterResponseStrategy::DoWork() {
  quint8 type = Parser::getRequestType(data_); 
  RegisterSuccessInfo info = Parser::ParseAsRegisterSuccessInfo(data_);
  if (type == static_cast<quint8>(ServerRequest::REGISTER_SUCCEED)) {
    emit RegisterResult(info.id);
  }
  if (type == static_cast<quint8>(ServerRequest::REGISTER_FAILED)) {
    emit RegisterResult(0);
  }
}
