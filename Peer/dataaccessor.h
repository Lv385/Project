#ifndef DATAACCESSOR_H
#define DATAACCESSOR_H

#include "..\DAL\sqldal.h"
#include "..\Common\client_data_types.h"

class DataAccessor {
 public:
  DataAccessor();
  ~DataAccessor();

  QString get_login_by_id(const unsigned& user_id);
  QPair<QString, int> get_ip_port(const unsigned& user_id);
  QVector<Friend> get_friends();
  QVector<Message> get_messages(const QString& user_login);
  QVector<Message> get_messages(const unsigned& user_id);

  Friend get_friend(const unsigned& user_id);
  unsigned get_id_by_login(const QString& user_login);
  bool get_friends_status(const unsigned& user_id);

  void set_friend_status(const unsigned& user_id, const bool& status);

  void AddFriend(const Friend& friend_info);
  void AddFriend(const unsigned& user_id, const QString& login,
                 const QString& ip = 0, const unsigned& port = 0,
                 const QString& name = 0, const QString& surname = 0);
  void AddMessageToDB(const QString& msg, const unsigned& user_id, const unsigned& owner_id);
  void AddMessageToDB(const Message& message);
   
  void SaveRequest(const FriendRequest& friend_request);
  QVector<FriendRequest> GetRequests();
  void DeleteRequest(const FriendRequest& friend_request);

  void UpdateIPPort(const unsigned& user_id, const QString& new_ip, const unsigned& new_port);

 private:
  dal::UnitOfWork db_;
  std::shared_ptr<dal::Friends> user_;
  std::shared_ptr<dal::Messages> message_;
  std::shared_ptr<dal::FriendRequests> friend_requests_;

};
#endif
