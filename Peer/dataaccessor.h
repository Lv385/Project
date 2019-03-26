#ifndef DATAACCESSOR_H
#define DATAACCESSOR_H

#include "sqldal.h"

class DataAccessor {
 public:
  DataAccessor();
  ~DataAccessor();

  QString GetLoginById(const unsigned user_id);
  QPair<QString, int> GetIPPort(const unsigned user_id);
  QVector<SQLDAL::Friend> GetFriends();
  QVector<SQLDAL::Message> GetMessages(const QString user_login);
  unsigned GetIDByLogin(const QString user_login);
  unsigned GetIDByIPPort(const QString ip, const unsigned port);
  bool GetFriendStatus(const unsigned user_id);

  void SetFriendStatus(const unsigned user_id, const bool status);

  void AddMessageToDB(const QString message, const unsigned user_id, const unsigned owner_id);
  void UpdateIPPort(const unsigned id, const QString new_ip, const unsigned new_port);

 private:
  SQLDAL::UnitOfWork db_;
  std::shared_ptr<SQLDAL::Friend> user_;
  std::shared_ptr<SQLDAL::Message> message_;
};
#endif
