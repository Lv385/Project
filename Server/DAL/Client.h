#pragma once
#include <iostream>
#include <vector>
#include <QHostAddress>
#include <QVector>

class AbstractRequest;//EPIC LINE OF CODE!!!!!

class Client
{
	friend std::ostream& operator<<(std::ostream &, const Client &);
public:
	Client();
	Client(QString, QString, QHostAddress, quint16);
	~Client();

	QString getUserName() const;
	void setUserName(QString &value);

	QHostAddress getUserIp() const;
	void setUserIp(const QHostAddress &value);

	quint16 getUserPort() const;
	void setUserPort(const quint16 value);

	quint32 getUserId() const;
	void setUserId(const quint32 id);

	QString getUserPassword() const;
	void setUserPassword(QString &value);

	void addFriend(Client&);
	void removeFriend(Client&);
	void setFriends(QVector<unsigned int> );
	QVector<unsigned int> getFriends();


	bool operator==(const Client &);

private:
	QString userName;//#0 indicies in a vector created after raw request parsing
	QString userPassword;//#1
	QHostAddress userIp;//#2
	quint16 userPort;//#3
	quint32 id;
	QVector<unsigned int> friends; // holds id of friends
	//std::vector<AbstractRequest*> pendingRequests;

};