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

	QString GetUserName() const;
	void SetUserName(QString &value);

	QHostAddress GetUserIp() const;
	void SetUserIp(const QHostAddress &value);

	quint16 GetUserPort() const;
	void SetUserPort(const quint16 value);

	quint32 GetUserId() const;
	void SetUserId(const quint32 id);

	QString GetUserPassword() const;
	void SetUserPassword(QString &value);

	void AddFriend(Client&);
	void RemoveFriend(Client&);
	void SetFriends(QVector<unsigned int> );
	QVector<unsigned int> GetFriends();


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