#ifndef CLIENTDB_H
#define CLIENTDB_H

#include <QtSql/qsqlresult.h>
#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QPair>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>
#include <iostream>

namespace ClientDAL 
{
	struct Message {
		int message_id;
		int owner_id;
		QString data;
		QDate date;
		QTime time;
		bool status;
	};

struct User {
  int user_id;
  // QString user_login;
  QString user_name;
  QString user_surname;
  // QImage user_profile_photo;
};

class ClientDB {
 public:
  ClientDB();
  ~ClientDB();

  void AddNewFriend(const QString& user_login, const int user_id);

  QPair<QString, int> GetIPPort(const QString& user_login);
  QPair<QString, int> GetIPPort(const int& user_id);

  void UpdateIPPort(const QString& user_login, const QString& new_user_ip,
                    const int& new_user_port);
  void UpdateIPPort(const int& user_id, const QString& new_user_ip,
                    const int& new_user_port);

  void AddMessage(const Message& message, const QString& user_login);
  void AddMessage(const Message& message, const int& user_id);

  QVector<Message> GetMessages(const QString& user_login);
  QVector<Message> GetMessages(const int& user_id);

  void UpdateUserProfile(const QString& user_login, const QString& user_name,
                         const QString& user_surname);
  void UpdateUserProfile(const int& user_id, const QString& user_name,
                         const QString& user_surname);

  QVector<User> GetFriends();
  QVector<QString> GetFriendsLogin();

  void DeleteFriend(const QString& user_login);
  void DeleteFriend(const int& user_id);

  void SetFriendStatus(const QString& user_login, bool status);
  void SetFriendStatus(const int& user_id, bool status);

  void SetMessageStatusRead(const int& message_id);

  bool GetFriendStatus(const QString& user_login);
  bool GetFriendStatus(const int& user_id);

  unsigned int GetIDByLogin(const QString& user_login);
  unsigned GetIDByIpPort(const QString& ip, int port);
  QString GetLoginById(const int& user_id);

 private:
  int CountOfFriends();
  int CountOfMessages(const QString& user_login);
  void CreateUserProfile(const unsigned int user_id);
  void DeleteUserProfile(const QString& user_login);
  void ErrorInfo(void);

  QSqlDatabase data_base_;
  QSqlQuery query_;
};

}  // namespace ClientDAL

#endif  // CLIENTDB_H
