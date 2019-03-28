#ifndef FRIEND_H
#define FRIEND_H
#include <qsqlrecord.h>
#include <QString>
#include "statement.h"
namespace SQLDAL {

  // This is our entity from database
  struct Friends {
	unsigned int id;
	QString		 ip;
	unsigned int port;
	QString      login;
	QString      name;
	QString      surname;
	bool         status;
	// IMAGE photo  //in progress
  };

  class Friend : public Statement {
   public:
	Friend(std::shared_ptr<Connect> Connect);
	Friend();

	QVector<Friends>	GetFriends();  // Getting all users
	Friends				GetFriend(const unsigned int id);
	void				UpdateFriend(Friends _friend);
	void				AddNewFriend(Friends _friend);
	void				DeleteFriend(Friends _friend);

   private:
	QString CreateQuerySelectAll();
	QString UpdateQuery(Friends _friend);
	QString SelectQuery(const unsigned int id);
	QString InsertQuery(Friends _friend);
	QString DeleteQuery(Friends _friend);
	QString CreateQueryCountOfFriends();
  };
}  // namespace SQLDAL
#endif  // FRIEND_H