#ifndef USER_H
#define USER_H
#include <QString>
#include "statement.h"
#include "sqldal.h"
namespace dal {

  class Users : public Statement {
  public:
	  Users(std::shared_ptr<Connect> Connect);
	  ~Users();

	  

	  User			 GetUser(const unsigned int& user_id);
	  User			 GetUser(const QString& user_login);// Select
	  void			 UpdateUser(User user);          // Update
	  void			 AddNewUser(User user);          // Insert
	  void			 DeleteUser(User user);          // Delete

	  QVector<UsersID>			 GetFriends(const unsigned int id);
	  QVector<UsersID>			 GetFriendsRequest(const unsigned int id);
	  QVector<UsersID>			 GetFriendsNotification(const unsigned int id);

	  void			 AddFriend(const UsersID& ids);
	  void			 AddFriendRequest(const UsersID& ids);
	  void			 AddFriendNotification(const UsersID& ids);

	  void           DeleteFriend(const UsersID& ids);
	  void			 DeleteFriendRequest(const UsersID& ids);
	  void			 DeleteFriendNotification(const UsersID& ids);
 
  private:
	  std::shared_ptr<FriendInfo>       friend_obj;
	  std::shared_ptr<RequestInfo>      request_obj;
	  std::shared_ptr<NotificationInfo> notification_obj;

	  QString							  UpdateQuery(User user);
	  QString							  SelectQuery(unsigned int user_id);
	  QString							  SelectQuery(QString user_login);
	  QString							  InsertQuery(User user);
	  QString							  DeleteQuery(User user);

  };

}
#endif  // !USER_H 
