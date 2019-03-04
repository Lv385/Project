#pragma once
#include <string>
#include <iostream>
#include <vector>

class AbstractRequest;//EPIC LINE OF CODE!!!!!

class Client
{
	friend std::ostream& operator<<(std::ostream &, const Client &);
public:
	Client();
	~Client();

	std::string getUserName() const;
	void setUserName(const std::string &value);

	std::string getUserIp() const;
	void setUserIp(const std::string &value);

	std::string getUserPort() const;
	void setUserPort(const std::string &value);

	std::string getUserPassword() const;
	void setUserPassword(const std::string &value);

	void addFriend(Client*);
	void removeFriend(Client*);

	bool operator==(const Client &);

private:
	std::string userName;//#0 indicies in a vector created after raw request parsing
	std::string userPassword;//#1
	std::string userIp;//#2
	std::string userPort;//#3
	std::vector<Client*> friends;
	std::vector<AbstractRequest*> pendingRequests;

};