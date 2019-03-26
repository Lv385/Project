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

		void			GetUser();             // Select
		void			UpdateUser();          // Update
		void			AddNewUser();          // Insert
		void			DeleteUser();          // Delete

	private:
		QString UpdateQuery();
		QString SelectQuery();
		QString InsertQuery();
		QString DeleteQuery();
		QString CountOfFriends();
		QString CountOfFriendsRequest();
	};
}
#endif  // !USER_H 
