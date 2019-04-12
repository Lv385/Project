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
  connect(object, SIGNAL(MessageRecieved(Message*)), clientController_,
          SIGNAL(MessageRecieved(Message*)));
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

void SignalRedirector::ConnectToFriendRequestResult(QObject *object) {
  connect(object, SIGNAL(FriendRequestResult(bool)), clientController_, 
    SIGNAL(FriendRequestResult(bool)));
}

void SignalRedirector::ConnectToAddFriendRequestInfo(QObject *object) {
  connect(object, SIGNAL(AddFriendRequestInfo(QString)), clientController_,
          SIGNAL(AddFriendRequestInfo(QString)));
}

void SignalRedirector::ConnectToNewFriendRequestResult(QObject *object) {
  connect(object, SIGNAL(NewFriendRequestResult(QString)), clientController_,
          SIGNAL(NewFriendRequestResult(QString)));
}

void SignalRedirector::set_controller(ClientController * controller) {
  clientController_ = controller;
}
