#pragma once
#include <iostream>
#include <vector>
#include <QHostAddress>

class AbstractRequest;//EPIC LINE OF CODE!!!!!

class Client
{
	friend std::ostream& operator<<(std::ostream &, const Client &);
public:
	Client();
	~Client();

	QString getUserName() const;
	void setUserName(QString &value);

	QHostAddress getUserIp() const;
	void setUserIp(const QHostAddress &value);

	quint16 getUserPort() const;
	void setUserPort(const quint16 value);

	QString getUserPassword() const;
	void setUserPassword(QString &value);

	void addFriend(Client*);
	void removeFriend(Client*);

	bool operator==(const Client &);

private:
	QString userName;//#0 indicies in a vector created after raw request parsing
	QString userPassword;//#1
	QHostAddress userIp;//#2
	quint16 userPort;//#3
	quint32 id;
	std::vector<Client*> friends;
	std::vector<AbstractRequest*> pendingRequests;

};