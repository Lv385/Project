#include "signalredirector.h"

SignalRedirector::SignalRedirector() {}

SignalRedirector &SignalRedirector::get_instance() {
  static SignalRedirector instance_;
  return instance_;
}

void SignalRedirector::ConnectToMessageSent(QObject *object) {
    connect(object, SIGNAL(MessageSent(unsigned, bool)), 
 clientController_, SIGNAL(MessageSent(unsigned, bool)));

}

void SignalRedirector::ConnectToMessageRecieved(QObject *object) {
  connect(object, SIGNAL(MessageRecieved(unsigned)), clientController_,
          SIGNAL(MessageRecieved(unsigned)));
}


void SignalRedirector::ConnectToLoginResult(QObject *object) {
  connect(object, SIGNAL(LoginResult(bool)), clientController_,
          SIGNAL(LoginResult(bool)));
}

void SignalRedirector::ConnectToRegisterResult(QObject *object) {
  connect(object, SIGNAL(RegisterResult(quint32)), clientController_,
          SIGNAL(RegisterResult(quint32)));
}

void SignalRedirector::ConnectToStatusChanged(QObject *object) {
  connect(object, SIGNAL(StatusChanged(unsigned, bool)), clientController_,
          SIGNAL(StatusChanged(unsigned, bool)));
}

void SignalRedirector::set_controller(ClientController * controller) {
  clientController_ = controller;
}
