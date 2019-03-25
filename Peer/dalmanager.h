#ifndef DALLMENEGER_H
#define DALLMENEGER_H

#include "sqldal.h"

class DALManager {
 public:
  DALManager();
  ~DALManager();

  QString GetLoginById(const unsigned user_id);
  QVector<QString> GetFriendsLogin();
  QPair<QString, int> GetIPPort(const unsigned user_id);
  QVector<SQLDAL::Friend> GetFriends();
  unsigned GetIDByLogin(const QString user_login);
  unsigned GetIDByIPPort(const QString ip, const unsigned port);
  QVector<SQLDAL::Message> GetMessages(const QString user_login);

  void SetFriendStatus(const unsigned user_id, const bool status);
  bool GetFriendStatus(const unsigned user_id);

  void AddMessageToDB(const QString message, const unsigned user_id, const unsigned owner_id);
  void UpdateIPPort(const unsigned id, const QString new_ip, const unsigned new_port);

 private:
  SQLDAL::UnitOfWork db_;
};
#endif
