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
  void AddPendingFriendRequest(Client &);
	void RemoveFriend(Client&);
	void SetFriends(QVector<unsigned int> );
	void Set_Pending_Request(QVector<unsigned int> );
	QVector<unsigned int> GetFriends();
	QVector<unsigned int>* Get_Pending_Requests();

	bool operator==(const Client &);

private:
	QString user_name;//#0 indicies in a vector created after raw request parsing
	QString user_password;//#1
	QHostAddress user_ip;//#2
	quint16 user_port;//#3
	quint32 id;
	QVector<unsigned int> friends; // holds id of current friends
	QVector<unsigned int> pending_requests_; //holds id of potential friends
	

};