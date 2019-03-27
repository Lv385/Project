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

		unsigned int	id;
		QString			login;
		QString			password;
		QString			ip;
		unsigned int	port;

		QVector<FriendInfo> friends; 
		QVector<RequestInfo> requests;
		QVector<NotificationInfo> notification;

		void			GetUser();             // Select
		void			UpdateUser();          // Update
		void			AddNewUser();          // Insert
		void			DeleteUser();          // Delete
		void			GetFriends();
		void			GetFriendsRequest();
		void			GetFriendsNotification();
		void			AddFriend(unsigned int id);
		void			AddFriendRequest(unsigned int id);
		void			AddFriendNotification(unsigned int id);

	private:
		std::shared_ptr<FriendInfo> friend_obj;
		std::shared_ptr<RequestInfo> request_obj;
		std::shared_ptr<NotificationInfo> notification_obj;
		QString UpdateQuery();
		QString SelectQuery();
		QString InsertQuery();
		QString DeleteQuery();
		QString CountOfFriends();
		QString CountOfFriendsRequest();
	};
}
#endif  // !USER_H 
