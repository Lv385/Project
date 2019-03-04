#include "client.h"


Client::Client()
{

}

Client::~Client()
{
	for (int i = 0; i < friends.size(); i++) {
		if (friends[i] != NULL) {
			delete friends[i];
		}
	}
}

std::string Client::getUserName() const
{
	return userName;
}

void Client::setUserName(const std::string &value)
{
	userName = value;
}

std::string Client::getUserIp() const
{
	return userIp;
}

void Client::setUserIp(const std::string &value)
{
	userIp = value;
}

std::string Client::getUserPort() const
{
	return userPort;
}

void Client::setUserPort(const std::string &value)
{
	userPort = value;
}

std::string Client::getUserPassword() const
{
	return userPassword;
}

void Client::setUserPassword(const std::string &value)
{
	userPassword = value;
}

void Client::addFriend(Client* cl)
{
	friends.push_back(cl);
}

void Client::removeFriend(Client * cl)
{
	for (int i = 0; i < friends.size(); i++) {
		if (friends[i] != NULL && friends[i] == cl) {
			delete friends[i];
		}
	}
}

bool Client::operator==(const Client &cl)
{
	return this->userName.compare(cl.userName) == 0;
}

std::ostream & operator<<(std::ostream & out, const Client& cl)
{
	out << cl.getUserName() << " " << cl.getUserIp() << " " << cl.getUserPassword() << " " << cl.getUserPort();
	return out;
}
