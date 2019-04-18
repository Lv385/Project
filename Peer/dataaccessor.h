#ifndef DATAACCESSOR_H
#define DATAACCESSOR_H

#include "..\DAL\sqldal.h"
#include "..\Common\client_data_types.h"

class DataAccessor {
 public:
  DataAccessor();
  ~DataAccessor();

  QString GetLoginById(const unsigned& user_id);
  QPair<QString, int> GetIpPort(const unsigned& user_id);
  QVector<Friend> GetFriends();
  QVector<Message> GetMessages(const QString& user_login);
  QVector<Message> GetMessages(const unsigned& user_id);

  Friend GetFriend(const unsigned& user_id);
  unsigned GetIdByLogin(const QString& user_login);
  bool GetFriendsStatus(const unsigned& user_id);

  void SetFriendStatus(const unsigned& user_id, const bool& status);

  void AddFriend(const Friend& friend_info);
  void AddFriend(const unsigned& user_id, const QString& login,
                 const QString& ip = 0, const unsigned& port = 0,
                 const QString& name = 0, const QString& surname = 0);
  void AddMessageToDB(const QString& msg, const unsigned& user_id, const unsigned& owner_id);
  void AddMessageToDB(const Message& message);
  void DeleteFriend(const unsigned& id);
   
  bool Exist(const FriendRequest& friend_request);
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
