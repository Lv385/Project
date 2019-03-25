#ifndef USER_H
#define USER_H
#include <QString>
#include "statement.h"
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

		void			AddNewFriendRequest(const unsigned int& friend_id);
		QVector<int>	GetFriendsRequest();  // SelectAllFriendsRequestAboutOneUser
		void			DeleteFriendRequest(const unsigned int& friend_id);

		void			GetUser();             // Select
		void			UpdateUser();          // Update
		void			AddNewUser();          // Insert
		void			DeleteUser();          // Delete

	private:
		QString InsertFriendRequestQuery(unsigned int friend_id);
		QString SelectFriendsRequestQuery();
		QString DeleteFriendRequestQuery(const unsigned int& friend_id);

		QString UpdateQuery();
		QString SelectQuery();
		QString InsertQuery();
		QString DeleteQuery();
		QString CountOfFriends();
		QString CountOfFriendsRequest();
	};
}
#endif  // !USER_H 
