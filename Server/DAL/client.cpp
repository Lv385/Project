#include "client.h"


Client::Client()
{

}

Client::Client(QString log, QString pas, QHostAddress i, quint16 p):
	userName(log), userPassword(pas), userIp(i), userPort(p)
{
}

Client::~Client()
{
	/*
	for (int i = 0; i < friends.size(); i++) {
		if (friends[i] != NULL) {
			delete friends[i];
		}
	}
	*/
}

QString Client::GetUserName() const
{
	return userName;
}

void Client::SetUserName( QString &value)
{
	userName = value;
}

QHostAddress Client::GetUserIp() const
{
	return userIp;
}

void Client::SetUserIp(const QHostAddress &value)
{
	userIp = value;
}

quint16  Client::GetUserPort() const
{
	return userPort;
}

void Client::SetUserPort(const quint16 value)
{
	userPort = value;
}

quint32 Client::GetUserId() const
{
	return id;
}

void Client::SetUserId(const quint32 i)
{
	id = i;
}

QString Client::GetUserPassword() const
{
	return userPassword;
}

void Client::SetUserPassword( QString &value)
{
	userPassword = value;
}

void Client::AddFriend(Client& cl)
{
	/*
	friends.push_back(cl);
	*/
}

void Client::RemoveFriend(Client & cl)
{
	/*
	for (int i = 0; i < friends.size(); i++) {
		if (friends[i] != NULL && friends[i] == cl) {
			delete friends[i];
		}
	}
	*/
}

void Client::SetFriends(QVector<unsigned int> f)
{
	friends = f;
}

QVector<unsigned int> Client::GetFriends()
{
	return friends;
}

bool Client::operator==(const Client &cl)
{
	return this->userName.compare(cl.userName) == 0;
}

std::ostream & operator<<(std::ostream & out, const Client& cl)
{
	out << cl.GetUserName().toStdString() << " " << cl.GetUserIp().toString().toStdString() << " " << cl.GetUserPassword().toStdString() << " " << cl.GetUserPort();
	return out;
}
