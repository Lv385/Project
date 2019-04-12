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
  void ConnectToLoginResult(QObject* object);
  void ConnectToRegisterResult(QObject* object);
  void ConnectToStatusChanged(QObject* object);
  void ConnectToFriendRequestResult(QObject* object);
  void ConnectToAddFriendRequestInfo(QObject* object);
  void ConnectToNewFriendRequestResult(QObject* object);

  void set_controller(ClientController*);

 private:
  SignalRedirector();
  ClientController* clientController_;
}; 



#endif  // !SIGNALREDIRECTOR_H
