#include "register_response_strategy.h"
#include "signalredirector.h"

RegisterResponseStrategy::RegisterResponseStrategy() 
  : AbstractStrategy() {
  redirector_.ConnectToRegisterResult(this);
}


RegisterResponseStrategy::~RegisterResponseStrategy()
{}

void RegisterResponseStrategy::DoWork() {
  ServerRequest type = static_cast<ServerRequest>(Parser::getRequestType(data_)); 
  RegisterSuccessInfo info = Parser::ParseAsRegisterSuccessInfo(data_);
  if (type == ServerRequest::REGISTER_SUCCEED) {
    emit RegisterResult(info.id);
  }
  if (type == ServerRequest::REGISTER_FAILED) {
    emit RegisterResult(0);
  }
}
