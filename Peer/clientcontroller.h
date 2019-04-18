#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include "config.h"

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
#include <QSettings>

#include "../Parser&Structs/request_types.h"

class SignalRedirector;

class ClientController : public QObject {
  Q_OBJECT

 public:
  ClientController(QObject* parent);
  ~ClientController();

  void SendMessage(const unsigned& id, const QString& message);
  void LogIn(const QString& login, const QString& password);
  void Register(const QString& login, const QString& password);
  void AddFriend(const QString& login);
  void DeleteFriend(const QString& login);
  void AddMeToDB();

  void FriendRequestAccepted(const QString& login);
  void FriendRequestRejected(const QString& login);

  void InitNetworkSettings();
  void GetIdByLogin(const QString& login);
  //QString GetMessage(unsigned);
  QVector<Message> LoadMessages(unsigned id);
  QVector<Friend> LoadFriends();

 signals:
  void MessagesSent(unsigned);
  void LoginResult(bool);
  void RegisterResult(quint32 id);
  void MessageRecieved(Message* message);
  void StatusChanged(unsigned id, bool status);
  void FriendRequestResult(bool);
  void AddFriendRequestInfo(QString);
  void NewFriendRequestResult(QString, quint32);
  void DeleteRequestResult(quint32);


 private slots:
  void OnNewConnection(QTcpSocket* socket);
  void OnStatusChanged(unsigned id, bool status);

 public slots:
  void OnLogin(bool);
  //void OnRegistered();

 private:
  void Start();
  void Stop();

 public:
  ApplicationInfo app_info_;

 private:
  FriendsUpdateManager* friends_update_manager_;
  CacheData& cache_data_;
  Friend my_info;
  QHash<unsigned, Friend> friends_cache;
  LocalServer local_server_;
  SignalRedirector& redirector_;
  FriendsManager friends_manager_;
  ServerManager* server_manager_;

  DataAccessor client_data_;
};

#endif  // !CLIENT_CONTROLLER_H
