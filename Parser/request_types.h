#ifndef REQUEST_TYPES_H
#define REQUEST_TYPES_H

#include <QtGlobal>
#include <QString>
#include <QHostAddress>

enum class ClientT : quint8
{
	MESSAGE = 0,
	LOGIN,
	REGISTER,
	LAST // this should be last to avoid errors
};

enum class ServerT : quint8
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
	QHostAddress ip;
	quint16 port;
	quint32 id;
};

struct FriendRequest
{

};

#endif // !REQUEST_TYPES_H
