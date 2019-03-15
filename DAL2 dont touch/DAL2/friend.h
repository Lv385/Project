#ifndef FRIEND_H
#define FRIEND_H
#include <QString>
#include<qsqlrecord.h>
#include "clientdal.h"

class Friend: public ClientDAL {
 public:
	 Friend(const QString &connection_name);
	 Friend();


  unsigned int id;
  QString ip;
  unsigned int port;
  QString login;
  QString name;
  QString surname;
  bool status;
  //IMAGE photo;

  QVector<Friend> GetFriends();//SelectAllInfoAboutOneChat
  void GetFriend();//Select
  //T GetListOfStatments<T>();//Select
  void UpdateFriendInfo();//Update
  void AddNewFriend();//Insert
  void DeleteFriend();//Delete

//private:
	QString CreateQuerySelectAll();
	QString CreateQuerySelect();
	QString CreateQueryInsert();
	QString CreateQueryUpdate();
	QString CreateQueryDelete();
	QString CreateQueryCountOfFriends();

};

#endif  // FRIEND_H