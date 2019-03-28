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
#include <QNetworkInterface>

#include "../Parser&Structs/request_types.h"

class ClientController : public QObject {
  Q_OBJECT

 public:
  ClientController(QObject* parent);
  ~ClientController();

  QVector<PeerInfo> LoadFriends();

  void SendMessage(PeerInfo peer_info, QString message);
  void LogIn(QString login, QString password);
  void Register(QString login, QString password);
  void AddFriend(QString login);

 signals:
  void messageReceived(quint32 id);
  void messageSent(quint32 id);
  void LoginResult(bool);
  void RegisterResult(quint32 id);
  void MessageRecieved(quint32 id);
  void StatusChanged(quint32 id, bool status);

 private:

 private slots:
  void OnNewConnection(QTcpSocket* socket);
  void OnFriendRequestRecieved();

 private:
  void Start();
  void Stop();

  FriendsUpdateManager* friendsupdate_manager;

  PeerInfo my_info;
  QHash<unsigned, PeerInfo> friends_cache;

  LocalServer local_server_;

  FriendsManager friend_manager_;
  ServerManager server_manager_;

  ApplicationInfo app_info_;
  DALManager dal;
};

#endif  // !CLIENT_CONTROLLER_H
