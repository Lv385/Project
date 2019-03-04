#pragma once
#include <string>
#include <map>
#include <iostream>
#include <string>

#include "client.h"
//using namespace std;


class DAL
{
public:
	DAL();
	//interface associated with database access will be placed here
	void setClient(Client);
	Client getClient(std::string);
	int getSize();
	void printDatabase();
private:

	std::map<std::string, Client> database;
};