#include "parser.h"

QByteArray Parser::LoginInfo_ToByteArray(LoginInfo & login_info)
{
	QByteArray result;
	QDataStream out(&result, QIODevice::WriteOnly);

	out << quint8(ClientRequest::LOGIN);		//type
	out << login_info.ip.toIPv4Address();		//ip
	out << login_info.port;						//port
	out << login_info.login;					//login
	out << login_info.password;					//password

	return result;
}

quint8 Parser::getRequestType(QByteArray & data)
{
	quint8 result = data.data()[0];
	return result;
}

LoginInfo Parser::ParseAsLoginInfo(QByteArray& data)
{
	LoginInfo result;

	QDataStream in(&data, QIODevice::ReadOnly);

	quint8 type;
	quint32 ip;
	in >> type >> ip >> result.port >> result.login >> result.password;
	result.ip = QHostAddress(ip);

	return result;
}

QByteArray Parser::FriendUpdateInfo_ToByteArray(FriendUpdateInfo & friend_update_info)
{
	QByteArray result;
	QDataStream out(&result, QIODevice::WriteOnly);

	out << quint8(ServerRequests::FRIEND_UPDATE_INFO);	    //type
	out << friend_update_info.ip.toIPv4Address();			//ip
	out << friend_update_info.port;							//port
	out << friend_update_info.id;							//id

	return result;
}

FriendUpdateInfo Parser::ParseAsFriendUpdateInfo(QByteArray& data)
{
	FriendUpdateInfo result;

	QDataStream in(&data, QIODevice::ReadOnly);

	quint8 type;								  
	quint32 ip;						

	in >> type >> ip >> result.port >> result.id;
	result.ip = QHostAddress(ip);

	return result;
}


QByteArray Parser::Message_ToByteArray(QString & message)
{
	QByteArray result;
	QDataStream out(&result, QIODevice::WriteOnly);

	out << quint8(ClientRequest::MESSAGE);				  //type
	out << message;										  //message

	return result;
}


QString Parser::ParseAsMessage(QByteArray& data)
{
	QString result;
	QDataStream in(&data, QIODevice::ReadOnly);

	quint8 type;

	in >> type >> result;

	return result;                           
}

QByteArray Parser::GetUnpossibleSequence()
{
	QByteArray result;

	QDataStream out(&result, QIODevice::WriteOnly);
	quint16 unpossible = 0xFFFE;
	out << unpossible;

	return result;
}


