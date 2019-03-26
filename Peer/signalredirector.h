#ifndef SIGNALREDIRECTOR_H
#define SIGNALREDIRECTOR_H

#include "clientcontroller.h"

#include <QObject>

class SignalRedirector : public QObject {
  Q_OBJECT

 public:
  static SignalRedirector& get_instance() {
    static SignalRedirector instance(nullptr);
    return instance;
  }
  SignalRedirector(SignalRedirector const&) = delete;
  void operator=(SignalRedirector const&) = delete;

  void ConnectToMessageSent(QObject* object);
  void ConnectToMessageRecieved(QObject* object);
  void ConnectToLoggedIn(QObject* object);

 private:
  SignalRedirector(QObject* parent);
  ClientController* clientController_;
};

#endif  // !SIGNALREDIRECTOR_H

