#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include "application_info.h"
#include "cachedata.h"
#include "friendsmanager.h"
#include "friendsupdatemanager.h"
#include "localserver.h"
#include "peerinfo.h"
#include "servermanager.h"

#include <QByteArray>
#include <QNetworkInterface>
#include <QObject>
#include <QTcpSocket>
#include <memory>

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
  void Start();
  void Stop();
  void SetAppInfo(ApplicationInfo info);
  //QString GetMessage(unsigned);
  QVector<SQLDAL::Message> LoadMessages(unsigned id);

 signals:

  void messageReceived(PeerInfo info, QString message);
  void messageSent(quint32 id);
  void LoginResult(bool);
  void RegisterResult(quint32 id);
  void MessageRecieved(unsigned id);
  void StatusChanged(quint32 id, bool status);

 private:
 private slots:
  void OnNewConnection(QTcpSocket* socket);
  void OnFriendRequestRecieved();

 public:
  ApplicationInfo app_info_;

 private:
  FriendsUpdateManager* friendsupdate_manager;
  CacheData& cache_data_;
  PeerInfo my_info;
  QHash<unsigned, PeerInfo> friends_cache;

  LocalServer local_server_;

  FriendsManager friend_manager_;
  ServerManager server_manager_;

  DataAccessor client_data_;
};

#endif  // !CLIENT_CONTROLLER_H
