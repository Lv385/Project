#ifndef USER_H
#define USER_H
#include <QString>
#include "connection.h"
#include "serverdal.h"

class  User : public ServerDAL{
 public:

	 User(const QString &connection_name);
	// ~User();

  unsigned int id;
  QString login;
  QString password;
  QString ip;
  unsigned int port;


  void GetUser();//Select
  void UpdateUser();//Update
  void AddNewUser();//Insert
  void DeleteUser();//Delete


//private:


	QString CreateQuerySelect();
	QString CreateQueryInsert();
	QString CreateQueryUpdate();
	QString CreateQueryDelete();

};

#endif  // !USER_H
