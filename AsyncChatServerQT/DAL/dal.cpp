#include "dal.h"


DAL::DAL()
{

}

void DAL::setClient(Client cl) {
	database[cl.getUserName()] = cl;
}
Client DAL::getClient(QString userName) {
	return database.at(userName);
}

int DAL::getSize()
{
	return database.size();
}

void DAL::printDatabase()
{
	for (auto& s : database)
	{
		std::cout << s.first.toStdString() << " " << s.second << std::endl;
	}
}
