#include "dal.h"


DAL::DAL()
{

}

void DAL::setClient(Client cl) {
	//database[cl.getUserName()] = cl;
	databse_.AddNewUser(cl.getUserName(),cl.getUserPassword());
	databse_.UpdateIPPort(cl.getUserName(),cl.getUserIp().toString(),(int)cl.getUserPort());
	

}
Client DAL::getClient(QString login) {
	//return database->at(userName);
	unsigned int id = databse_.GetIDByLogin(login);
	Client toReturn;
	if ( id!= 0) {
		
		toReturn.setUserId(id);
		toReturn.setUserIp(QHostAddress(databse_.GetIPPort(id).first));
		toReturn.setUserPort((quint16)databse_.GetIPPort(id).second);
		toReturn.setUserName(databse_.GetLoginByID(id));
		toReturn.setUserPassword(databse_.GetPasswordById(id));
		toReturn.setFriends(databse_.GetFriends(id));
	}
	return toReturn;
	
	//databse_.
	/*
	toReturn.setUserId(databse_.GetIDByLogin(login));
	QPair<QString, int> ip_port = databse_.GetIPPort(login, 0);
	toReturn.setUserIp(ip_port.first);
	if (databse_.isFriend(0, 0)) {
		printdatabase->
		*/
}

Client DAL::getClient(quint32 i)
{
	return this->getClient(databse_.GetLoginByID(i));
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
