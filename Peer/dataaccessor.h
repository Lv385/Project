#ifndef DATAACCESSOR_H
#define DATAACCESSOR_H

#include "sqldal.h"

class DataAccessor {
 public:
  DataAccessor();
  ~DataAccessor();

  QString get_login_by_id(const unsigned user_id);
  QPair<QString, int> get_ip_port(const unsigned user_id);
  QVector<SQLDAL::Friends> get_friends();
  QVector<SQLDAL::Messages> get_messages(const QString user_login);
  QVector<SQLDAL::Messages> get_messages(unsigned user_id);

  unsigned get_id_by_login(const QString user_login);
  //unsigned get_id_by_ip_port(const QString ip, const unsigned port);
  bool get_friends_status(const unsigned user_id);

  void set_friend_status(const unsigned user_id, const bool status);

  void AddMessageToDB(const QString msg, const unsigned user_id, const unsigned owner_id);
  void UpdateIPPort(const unsigned user_id, const QString new_ip, const unsigned new_port);

 private:
  SQLDAL::UnitOfWork db_;
  std::shared_ptr<SQLDAL::Friend> user_;
  std::shared_ptr<SQLDAL::Message> message_;
};
#endif
