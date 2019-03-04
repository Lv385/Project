#ifndef PARSER_H
#define PARSER_H

#include <QByteArray>
#include <QDataStream>

#include "request_types.h"

class Parser
{
public:
	static quint8  getRequestType(QByteArray& data);

	static LoginOrRegisterInfo		ParseAsLoginOrRegisterInfo(QByteArray& data);
	static FriendUpdateInfo ParseAsFriendUpdateInfo(QByteArray& data);
	static QString          ParseAsMessage(QByteArray& data);

	static QByteArray		LoginOrRegisterInfo_ToByteArray(LoginOrRegisterInfo& login_info);
	static QByteArray		FriendUpdateInfo_ToByteArray(FriendUpdateInfo& friend_update_info);
	static QByteArray       Message_ToByteArray(QString& message);

	static QByteArray       GetUnpossibleSequence();  //hardcode, this shoud be added to the end of any QByteArray that is written by socket
													  //to awoid erros
													  //hoping that this sequence will 
													  //not appear in any of our messages
													  //must be fixed
	static QByteArray       yesNoResponseToByteArray(quint8 type);
};

#endif // PARSER_H