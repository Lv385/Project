#ifndef FRIEND_H
#define FRIEND_H

#include <QString>
#include <qsqlrecord.h>
#include "statement.h"

namespace SQLDAL {

  // This is our entity from database
  struct Friends {
	unsigned int id;
	QString		   ip;
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
	Friends				GetFriend(const QString& login);
	void				UpdateFriend(const Friends& _friend);
	void				AddNewFriend(const Friends& _friend);
	void				DeleteFriend(const Friends& _friend);

   private:
	QString CreateQuerySelectAll();
    QString UpdateQuery(const Friends& _friend);
	QString SelectQuery(const unsigned int id);
	QString SelectQuery(const QString& login);
    QString InsertQuery(const Friends& _friend);
	QString DeleteQuery(const Friends& _friend);
	QString CreateQueryCountOfFriends();
  };
}  // namespace SQLDAL
#endif  // FRIEND_H