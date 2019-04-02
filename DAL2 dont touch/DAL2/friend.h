#ifndef FRIEND_H
#define FRIEND_H

#include <QString>
#include <qsqlrecord.h>
#include "statement.h"

namespace SQLDAL {

  // This is our entity from database
  struct Friend {
	unsigned int id;
	QString		   ip;
	unsigned int port;
	QString      login;
	QString      name;
	QString      surname;
	bool         status;
	// IMAGE photo  //in progress
  };

  class Friends : public Statement {
   public:
	Friends(std::shared_ptr<Connect> Connect);
	Friends();

	QVector<Friend>	GetFriends();  // Getting all users
	Friend				GetFriend(const unsigned int id);
	Friend				GetFriend(const QString& login);
	void				UpdateFriend(const Friend& _friend);
	void				AddNewFriend(const Friend& _friend);
	void				DeleteFriend(const Friend& _friend);

   private:
	QString CreateQuerySelectAll();
    QString UpdateQuery(const Friend& _friend);
	QString SelectQuery(const unsigned int id);
	QString SelectQuery(const QString& login);
    QString InsertQuery(const Friend& _friend);
	QString DeleteQuery(const Friend& _friend);
	QString CreateQueryCountOfFriends();
  };
}  // namespace SQLDAL
#endif  // FRIEND_H