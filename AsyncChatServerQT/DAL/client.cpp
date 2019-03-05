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

QString Client::getUserName() const
{
	return userName;
}

void Client::setUserName( QString &value)
{
	userName = value;
}

QHostAddress Client::getUserIp() const
{
	return userIp;
}

void Client::setUserIp(const QHostAddress &value)
{
	userIp = value;
}

quint16  Client::getUserPort() const
{
	return userPort;
}

void Client::setUserPort(const quint16 value)
{
	userPort = value;
}

QString Client::getUserPassword() const
{
	return userPassword;
}

void Client::setUserPassword( QString &value)
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
	out << cl.getUserName().toStdString() << " " << cl.getUserIp().toString().toStdString() << " " << cl.getUserPassword().toStdString() << " " << cl.getUserPort();
	return out;
}
