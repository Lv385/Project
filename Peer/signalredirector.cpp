#include "signalredirector.h"

SignalRedirector::SignalRedirector(QObject *parent)
    : QObject(parent)
{
}

void SignalRedirector::ConnectToMessageSent(QObject *object) { 
  connect(object, SIGNAL(messageSent()),  
                  clientController_, SIGNAL(messageSent()));

}

void SignalRedirector::ConnectToMessageRecieved(QObject *object) {}

void SignalRedirector::ConnectToLoggedIn(QObject *object) {}

