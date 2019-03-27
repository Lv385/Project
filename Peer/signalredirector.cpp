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

void SignalRedirector::ConnectToLoggedIn(QObject *object) {
}

void ConnectToMessageSent(QObject *object) {
}