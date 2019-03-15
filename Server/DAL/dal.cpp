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

void DAL::CreateNew(Client cl) {
   // this function is only for new user request (register)
  database_.AddNewUser(cl.GetUserName(), cl.GetUserPassword());
  database_.UpdateIPPort(cl.GetUserName(), cl.GetUserIp().toString(), (int)cl.GetUserPort());
}

void DAL::SetClientIpPort(Client cl) {
   //  this is used when login   and MAYBE  when adding to friend 
	database_.UpdateIPPort(cl.GetUserName(),cl.GetUserIp().toString(),(int)cl.GetUserPort());
}
Client DAL::getClient(QString login) {
	
	unsigned int id = database_.GetIDByLogin(login);
  if (id == 0) {
          throw UserNotFound();
  }
	  Client toReturn;		
		toReturn.SetUserId(id);
		toReturn.SetUserIp(QHostAddress(database_.GetIPPort(id).first));
		toReturn.SetUserPort((quint16)database_.GetIPPort(id).second);
		toReturn.SetUserName(database_.GetLoginByID(id));
		toReturn.SetUserPassword(database_.GetPasswordById(id));
		toReturn.SetFriends(database_.GetFriends(id));
	
	return toReturn;
	
}

Client DAL::getClient(quint32 i) {
  return getClient(database_.GetLoginByID(i));
}

bool DAL::Check_If_Client_exists_In_Db(Client cl) {
  if (database_.GetIDByLogin(cl.GetUserName()) == 0) {         // If login don't exist return id = 0
    
	return false;// login dont exist
	
  } else {

    return true;  // login exist
  }
}

bool DAL::Check_If_Client_exists_In_Db(QString login)
{
  if (database_.GetIDByLogin(login) == 0) {         // If login don't exist return id = 0

    return false;// login dont exist

  }
  else {

    return true;  // login exist
  }
  return false;
}

int DAL::GetClientId(Client cl)
{
	return database_.GetIDByLogin(cl.GetUserName());
}


