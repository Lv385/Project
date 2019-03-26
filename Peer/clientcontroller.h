#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include <QHash>
#include <QObject>
#include <QSet>

#include "../Parser&Structs/request_types.h"
#include "friendsupdatemanager.h"
#include "peerinfo.h"
#include "workmanager.h"

class ClientController : public QObject {
  Q_OBJECT

 public:
  ClientController(QObject* parent);
  ~ClientController();

 signals:
  void messageReceived();
  void messageSent();

  private :
  
  void SendMessage(PeerInfo peer_info, QString message);
  void LogIn(QString login, QString password);
  void Register();
  void AddFriend();
  void DeleteFriend();
  void OnFriendRequestRecieved();

 private:
  void Start();
  void Stop();

  WorkManager* work_manager_;
  FriendsUpdateManager* friendsupdate_manager;

  PeerInfo my_info;
  QHash<unsigned, PeerInfo> friends_cache;
};

#endif  // !CLIENT_CONTROLLER_H
