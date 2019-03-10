#include "dal.h"


DAL::DAL()
{

}

void DAL::setClient(Client cl) {
	//database[cl.getUserName()] = cl;
	databse_.AddNewUser(cl.GetUserName(),cl.GetUserPassword());
	databse_.UpdateIPPort(cl.GetUserName(),cl.GetUserIp().toString(),(int)cl.GetUserPort());
	

}
Client DAL::getClient(QString login) {
	//return database->at(userName);
	unsigned int id = databse_.GetIDByLogin(login);
	Client toReturn;
	if ( id!= 0) {
		
		toReturn.SetUserId(id);
		toReturn.SetUserIp(QHostAddress(databse_.GetIPPort(id).first));
		toReturn.SetUserPort((quint16)databse_.GetIPPort(id).second);
		toReturn.SetUserName(databse_.GetLoginByID(id));
		toReturn.SetUserPassword(databse_.GetPasswordById(id));
		toReturn.SetFriends(databse_.GetFriends(id));
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

Client DAL::getClient(quint32 i)
{
	return this->getClient(databse_.GetLoginByID(i));
}

bool DAL::Check_If_Client_exists_In_Db(Client cl)
{
	if (databse_.GetIDByLogin(cl.GetUserName()) == 0) { // If login don't exist return id = 0
		return false; // login dont exist
	} else {
		return true; //login exist 
	}
	
}

int DAL::GetClientId(Client cl)
{
	return databse_.GetIDByLogin(cl.GetUserName());
}


/*

int DAL::getSize()
{
	return database->size();
}

void DAL::printDatabase()
{
	for (auto& s : database)
	{
		std::cout << s.first.toStdString() << " " << s.second << std::endl;
	}
}
*/
