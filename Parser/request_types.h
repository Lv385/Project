#ifndef REQUEST_TYPES_H
#define REQUEST_TYPES_H

#include <QString>
#include <QHostAddress>


enum class ClientT : char
{
	MESSAGE = 0,
	LOGIN,
	REGISTER,
	LAST // this should be last to avoid errors
};

enum class ServerT : char
{
	LOGIN_SUCCEED = (char)ClientT::LAST + 1,
	LOGIN_FAILED,

	REGISTER_SUCCEED, 
	REGISTER_FAILED, 

	FRIEND_UPDATE_INFO	
};

struct LoginInfo
{
	QHostAddress ip;
	quint16 port;
	QString login;
	QString password;
};

struct FriendUpdateInfo
{
	int id;
	QHostAddress ip;
	quint16 port;
};

struct FriendRequest
{

};

struct IPv4
{
	char byte1;
	char byte2;
	char byte3;
	char byte4;
};
#endif // !REQUEST_TYPES_H
