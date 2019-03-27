#ifndef SIGNALREDIRECTOR_H
#define SIGNALREDIRECTOR_H

#include <QObject>
#include "clientcontroller.h"

class SignalRedirector : public QObject {
  Q_OBJECT
 public:
  static SignalRedirector& get_instance();
  SignalRedirector(SignalRedirector const&) = delete;
  void operator=(SignalRedirector const&) = delete;

  void ConnectToMessageSent(QObject* object);
  void ConnectToMessageRecieved(QObject* object);
  void ConnectToLoggedIn(QObject* object);

 private:
  SignalRedirector();
  ClientController* clientController_;
}; 



#endif  // !SIGNALREDIRECTOR_H
