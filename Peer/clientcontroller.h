#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include "application_info.h"
#include "cachedata.h"
#include "friendsmanager.h"
#include "friendsupdatemanager.h"
#include "localserver.h"
 
#include "servermanager.h"

#include <QByteArray>
#include <QNetworkInterface>
#include <QObject>
#include <QTcpSocket>
#include <memory>

#include "../Parser&Structs/request_types.h"

class SignalRedirector;

class ClientController : public QObject {
  Q_OBJECT

 public:
  ClientController(QObject* parent);
  ~ClientController();


  void SendMessage(unsigned id, QString message);
  void LogIn(QString login, QString password);
  void Register(QString login, QString password);
  void AddFriend(QString login);
  void Start();
  void Stop();
  void SetAppInfo(ApplicationInfo info);
  //QString GetMessage(unsigned);
  QVector<Message> LoadMessages(unsigned id);
  QVector<Friend> LoadFriends();

 signals:

  void MessageSent(unsigned, bool);
  void LoginResult(bool);
  void RegisterResult(quint32 id);
  void MessageRecieved(Message* message);
  void StatusChanged(unsigned id, bool status);

 private slots:
  void OnNewConnection(QTcpSocket* socket);
  void OnFriendRequestRecieved();

 public:
  ApplicationInfo app_info_;

 private:
  FriendsUpdateManager* friendsupdate_manager;
  CacheData& cache_data_;
  Friend my_info;
  QHash<unsigned, Friend> friends_cache;

  LocalServer local_server_;
  SignalRedirector& redirector_;
  FriendsManager friend_manager_;
  ServerManager* server_manager_;

  DataAccessor client_data_;
};

#endif  // !CLIENT_CONTROLLER_H
