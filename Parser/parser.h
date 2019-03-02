#ifndef PARSER_H
#define PARSER_H

#include <QByteArray>
#include <QDataStream>

#include "../Parser/request_types.h"

class Parser
{
public:
	quint8 static getRequestType(QByteArray& data);

	static LoginInfo		ParseAsLoginInfo(QByteArray& data);
	static FriendUpdateInfo ParseAsFriendUpdateInfo(QByteArray& data);
	static QString          ParseAsMessage(QByteArray& data);

	static QByteArray		LoginInfo_ToByteArray(LoginInfo& login_info);
	static QByteArray		FriendUpdateInfo_ToByteArray(FriendUpdateInfo& friend_update_info);
	static QByteArray       Message_ToByteArray(QString& message);
};

#endif // PARSER_H