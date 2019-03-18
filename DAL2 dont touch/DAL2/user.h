#ifndef USER_H
#define USER_H
#include <QString>
#include "connection.h"
#include "statement.h"

class User : public Statement {
 public:
  User(std::shared_ptr<Connection> connection);
  ~User();

  unsigned int	id;
  QString		login;
  QString		password;
  QString		ip;
  unsigned int	port;

  QVector<int>	GetFriends();  // SelectAllFriendsAboutOneUser
  void			GetUser();             // Select
  void			UpdateUser();          // Update
  void			AddNewUser();          // Insert
  void			DeleteUser();          // Delete

 private:
  QString SelectFriendsQuery();
  QString UpdateQuery();
  QString SelectQuery();
  QString InsertQuery();
  QString DeleteQuery();
  QString CountOfFriends();
};

#endif  // !USER_H
