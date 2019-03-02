#ifndef PARSER_H
#define PARSER_H

#include <QByteArray>

#include "../Parser/request_types.h"

class Parser
{
public:
	Parser() = delete;
	static LoginInfo		ParseAsLoginInfo(QByteArray& data);
	static FriendUpdateInfo ParseAsFriendUpdateInfo(QByteArray& data);
	static QString          ParseAsMessage(QByteArray& data);

	static QByteArray		LoginInfo_ToByteArray(LoginInfo& login_info);
	static QByteArray		FriendUpdateInfo_ToByteArray(FriendUpdateInfo& friend_update_info);
	static QByteArray       Message_ToByteArray(QString& message);
};

#endif // PARSER_H