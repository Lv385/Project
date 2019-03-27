#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include "friendsupdatemanager.h"
#include "peerinfo.h"
#include "servermanager.h"
#include "application_info.h"
#include "localserver.h"
#include "friendsmanager.h"
#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
#include <memory>

#include "../Parser&Structs/request_types.h"

class ClientController : public QObject {
  Q_OBJECT

 public:
  ClientController(QObject* parent);
  ~ClientController();

 signals:
  void messageReceived();
  void messageSent();
  void LoggedIn();
  void Registered();

 private:
  void SendMessage(PeerInfo peer_info, QString message);
  void LogIn(QString login, QString password);
  void Register();
  void AddFriend();
  void DeleteFriend();
  void OnFriendRequestRecieved();

 private slots:
  void OnNewConnection(QTcpSocket* socket);

 private:
  void Start();
  void Stop();

  FriendsUpdateManager* friendsupdate_manager;

  PeerInfo my_info;
  QHash<unsigned, PeerInfo> friends_cache;

  LocalServer* local_server_;

  FriendsManager client_worker_;
  ServerManager server_worker_;

  ApplicationInfo app_info_;
};

#endif  // !CLIENT_CONTROLLER_H
