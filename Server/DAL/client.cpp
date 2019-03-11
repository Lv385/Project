#include "client.h"


Client::Client()
{

}

Client::Client(QString log, QString pas, QHostAddress i, quint16 p):
	user_name(log), user_password(pas), user_ip(i), user_port(p)
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
	return user_name;
}

void Client::SetUserName( QString &value)
{
	user_name = value;
}

QHostAddress Client::GetUserIp() const
{
	return user_ip;
}

void Client::SetUserIp(const QHostAddress &value)
{
	user_ip = value;
}

quint16  Client::GetUserPort() const
{
	return user_port;
}

void Client::SetUserPort(const quint16 value)
{
	user_port = value;
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
	return user_password;
}

void Client::SetUserPassword( QString &value)
{
	user_password = value;
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
	return this->user_name.compare(cl.user_name) == 0;
}

std::ostream & operator<<(std::ostream & out, const Client& cl)
{
	out << cl.GetUserName().toStdString() << " " << cl.GetUserIp().toString().toStdString() << " " << cl.GetUserPassword().toStdString() << " " << cl.GetUserPort();
	return out;
}
