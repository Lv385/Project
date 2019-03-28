#include "signalredirector.h"

SignalRedirector::SignalRedirector() {}

void SignalRedirector::ConnectToMessageSent(QObject *object) {
    connect(object, SIGNAL(messageSent()), 
 clientController_, SIGNAL(messageSent()));
}

void SignalRedirector::ConnectToMessageRecieved(QObject *object) {
}

SignalRedirector& SignalRedirector::get_instance() {
  static SignalRedirector instance_;
  return instance_;
}

void SignalRedirector::ConnectToLoginResult(QObject *object) {
  connect(object, SIGNAL(LoginResult(bool)), clientController_,
          SIGNAL(LoginResult(bool)));
}

void SignalRedirector::ConnectToRegisterResult(QObject *object) {
  connect(object, SIGNAL(RegisterResult(quint32)), clientController_,
          SIGNAL(RegisterResult(quint32)));
}

void ConnectToMessageSent(QObject *object) {
}