#ifndef FRIEND_H
#define FRIEND_H
#include <QString>
#include <qsqlrecord.h>
#include "statement.h"

class Friend : public Statement {
 public:
  Friend(std::shared_ptr<Connection> connection);
  Friend();

  unsigned int	  id;
  QString		  ip;
  unsigned int	  port;
  QString		  login;
  QString		  name;
  QString		  surname;
  bool			  status;
  // IMAGE photo;

  QVector<Friend> GetFriends();  // SelectAllInfoAboutOneChat
  void			  GetFriend();
  void			  UpdateFriend();
  void			  AddNewFriend();
  void			  DeleteFriend();

  private:
  QString CreateQuerySelectAll();
  QString UpdateQuery();
  QString SelectQuery();
  QString InsertQuery();
  QString DeleteQuery();
  QString CreateQueryCountOfFriends();
};

#endif  // FRIEND_H