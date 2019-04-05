#include "login_response_strategy.h"
#include "signalredirector.h"

LoginResponseStrategy::LoginResponseStrategy()
  : AbstractStrategy(){
  redirector_.ConnectToLoginResult(this);
  this->dumpObjectInfo();
}

LoginResponseStrategy::~LoginResponseStrategy() {}

void LoginResponseStrategy::DoWork() {
  quint8 type = Parser::getRequestType(data_); 
  if(type == static_cast<quint8>(ServerRequest::LOGIN_SUCCEED)){
    emit LoginResult(true);
  }
  if(type == static_cast<quint8>(ServerRequest::LOGIN_FAILED)){
    emit LoginResult(false);
  }
}
