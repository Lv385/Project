#ifndef SEVERDB_H
#define SEVERDB_H

#include <QDebug>
#include <QObject>
#include <QPair>
#include <QSqlRecord>
#include <QSqlResult>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <iostream>

// Class contains all methods needed to work with db.
// Each server or client thread must hold instance
// of this class to perform db tasks
class ServerDB {
 public:
  // Following two function must appear in pairs (always call CloseConncetion()
  // after NewConnection() with the same name
  void NewConnection(const QString connection_name);
  void CloseConncetion(const QString connection_name);

  void AddNewUser(const QString& new_user_login,
                  const QString& new_user_password);

  void UpdateIPPort(const QString& user_login, const QString& new_user_ip,
                    const int& new_user_port); 
  void UpdateIPPort(const unsigned int& user_id, const QString& new_user_ip,
                    const int& new_user_port);  

  QPair<QString, int> GetIPPort(const QString& user_login);
  QPair<QString, int> GetIPPort(const unsigned int& user_id);

  bool CheckUser(const QString& user_login, const QString& user_password);
  QString GetPasswordById(const unsigned int& user_id);  
  
  void AddFriend(const QString& user_login, const QString& second_user_login);
  void AddFriend(const unsigned int& user_id, const unsigned int& second_user_id);

  void DeleteAllFriends(const unsigned int& user);

  void DeleteAllPendingRequest(const unsigned int& user);
  void DeleteAllPendingNotifications(const unsigned int& user);

  // If login don't exist return id = 0
  unsigned int GetIDByLogin( const QString& user_login); 

  // String will be empty if user id dont exist
  QString GetLoginByID(const unsigned int& user_id);  

  QVector<unsigned int> GetFriends(unsigned const int& user_id);

  void addPendingFriendRequest(const unsigned int& user_id, const unsigned int& pending_user);
  QVector<unsigned int> GetPendingFriendRequests(unsigned const int& user_id);

  void addPendingNotification(const unsigned int& user_id, const unsigned int& pending_user);
  QVector<unsigned int> GetPendingNotification(unsigned const int& user_id);

  bool IsFriend(const QString& first_user_login, const QString& second_user_login);
  bool IsFriend(const unsigned int& first_user_id, const unsigned int& second_user_id);

 private:
  int FindMaxID();  // Find maximal id in the table, if something go wrong
                    // return -1
  void ErrorInfo();
  bool IsLoginExist(const QString& user_login);  // Check that user exist

  QSqlQuery* query_;  // before closing database connection all instances of
                      // QSqlQuery should be deleted
};

#endif  // SEVERDB_H
