#include "dal.h"


DAL::DAL()
{ 
  QUuid uuid;
  connection_name_ = uuid.createUuid().toString();
  database_.NewConnection(connection_name_);
}

DAL::~DAL() { 
  database_.CloseConncetion(connection_name_); 
}

void DAL::SetClient(Client cl) {
	//database[cl.getUserName()] = cl;
	//database_.AddNewUser(cl.GetUserName(),cl.GetUserPassword());
	database_.UpdateIPPort(cl.GetUserName(),cl.GetUserIp().toString(),(int)cl.GetUserPort());
	

}
Client DAL::getClient(QString login) {
	//return database->at(user_name);
	unsigned int id = database_.GetIDByLogin(login);
	Client toReturn;
	if ( id!= 0) {
		
		toReturn.SetUserId(id);
		toReturn.SetUserIp(QHostAddress(database_.GetIPPort(id).first));
		toReturn.SetUserPort((quint16)database_.GetIPPort(id).second);
		toReturn.SetUserName(database_.GetLoginByID(id));
		toReturn.SetUserPassword(database_.GetPasswordById(id));
		toReturn.SetFriends(database_.GetFriends(id));
	}
	return toReturn;
	
	//databse_.
	/*
	toReturn.SetUserId(databse_.GetIDByLogin(login));
	QPair<QString, int> ip_port = databse_.GetIPPort(login, 0);
	toReturn.SetUserIp(ip_port.first);
	if (databse_.isFriend(0, 0)) {
		printdatabase->
		*/
}

Client DAL::getClient(quint32 i) {
  /*return this-> getClient(databse_.GetLoginByID(i));*/
  return getClient(database_.GetLoginByID(i));
}

bool DAL::Check_If_Client_exists_In_Db(Client cl) {
  if (database_.GetIDByLogin(cl.GetUserName()) ==
      0) {         // If login don't exist return id = 0
    return false;  // login dont exist
  } else {
    return true;  // login exist
  }
}

int DAL::GetClientId(Client cl)
{
	return database_.GetIDByLogin(cl.GetUserName());
}


