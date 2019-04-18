#include "login_response_strategy.h"
#include "signalredirector.h"

LoginResponseStrategy::LoginResponseStrategy()
  : AbstractStrategy(){
  redirector_.ConnectToLoginResult(this);
}

LoginResponseStrategy::~LoginResponseStrategy() {}

void LoginResponseStrategy::DoWork() {
  ServerRequest type = static_cast<ServerRequest> (Parser::getRequestType(data_)); 
  if(type == ServerRequest::LOGIN_SUCCEED){
  emit LoginResult(true);
  }
  if(type == ServerRequest::LOGIN_FAILED){
    emit LoginResult(false);
  }
}
