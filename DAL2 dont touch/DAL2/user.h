#ifndef USER_H
#define USER_H
#include <QString>
#include "statement.h"
#include "sqldal.h"
namespace SQLDAL {

  class User : public Statement {
  public:
	  User(std::shared_ptr<Connect> Connect);
	  ~User();
      /*Columns from table */
	  unsigned int	    id;
	  QString			login;
	  QString			password;
	  QString			ip;
	  unsigned int		port;

      /* Vectors to show our relations */
	  QVector<UsersID> friends; 
	  QVector<UsersID> requests;
	  QVector<UsersID> notification;

	  void			 GetUser(const unsigned int& user_id);
	  void			 GetUser(const QString& user_login);// Select
	  void			 UpdateUser();          // Update
	  void			 AddNewUser();          // Insert
	  void			 DeleteUser();          // Delete

	  void			 GetFriends();
	  void			 GetFriendsRequest();
	  void			 GetFriendsNotification();

	  void			 AddFriend(unsigned int user_id);
	  void			 AddFriendRequest(unsigned int user_id);
	  void			 AddFriendNotification(unsigned int user_id);
	  void           DeleteFriend(unsigned int user_id);
	  void			 DeleteFriendRequest(unsigned int user_id);
	  void			 DeleteFriendNotification(unsigned int user_id);
 
  private:
	  std::shared_ptr<FriendInfo>       friend_obj;
	  std::shared_ptr<RequestInfo>      request_obj;
	  std::shared_ptr<NotificationInfo> notification_obj;

	  QString							  UpdateQuery();
	  QString							  SelectQuery(unsigned int user_id);
	  QString							  SelectQuery(QString user_login);
	  QString							  InsertQuery();
	  QString							  DeleteQuery();
	  QString							  CountOfFriends();
	  QString							  CountOfFriendsRequest();
  };

}
#endif  // !USER_H 
