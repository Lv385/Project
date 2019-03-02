#include "../Parser/parser.h"



QByteArray Parser::LoginInfo_ToByteArray(LoginInfo & login_info)
{
	QByteArray result;

	//type
	result.append(char(ClientT::LOGIN));

	//ip
	quint32 temp = login_info.ip.toIPv4Address();
	result.append((char*)&temp, sizeof(quint32));

	//port
	result.append((char*)&login_info.port, 2);

	//login
	result.append(login_info.login);
	result.append('#');

	//password
	result.append(login_info.password);

	return result;
}

LoginInfo Parser::ParseAsLoginInfo(QByteArray& data)
{
	LoginInfo result;

	//ip
	quint32 ipv4;
	memcpy(&ipv4, data.data() + 1, 4);		                  // first byte is type, sizeof(quint32) == 4
	result.ip.setAddress(ipv4);						          
													          
	//port											          
	memcpy(&result.port, data.data() + 5, 2);		          //sizeof(quint32) == 4, so start at 5, sizeof(quint) is 2
													          
	//login											          
	result.login = data.mid(7, data.indexOf('#') - 7);        //sizeof(quint) is 2, so start at 7 to #
													          
	//password										          
	result.password = data.mid(data.indexOf('#') + 1);        //without #

	return result;
}


QByteArray Parser::FriendUpdateInfo_ToByteArray(FriendUpdateInfo & friend_update_info)
{
	QByteArray result;

	//type
	result.append(char(ServerT::FRIEND_UPDATE_INFO));

	//ip
	quint32 temp = friend_update_info.ip.toIPv4Address();
	result.append((char*)&temp, sizeof(quint32));

	//port
	result.append((char*)&friend_update_info.port, 2);

	//id
	result.append((char*)&friend_update_info.id, sizeof(int));

	return result;
}

FriendUpdateInfo Parser::ParseAsFriendUpdateInfo(QByteArray& data)
{
	FriendUpdateInfo result;
	//ip
	quint32 ipv4;
	memcpy(&ipv4, data.data() + 1, 4);					     //first byte is type, sizeof(quint32) == 4
	result.ip.setAddress(ipv4);

	//port
	memcpy(&result.port, data.data() + 5, 2);                //sizeof(quint32) == 4, so start at 5, sizeof(quint) is 2

	//id
	memcpy(&result.port, data.data() + 7, sizeof(int));      //sizeof(quint) is 2, so start at 7

	return result;
}


QByteArray Parser::Message_ToByteArray(QString & message)
{
	QByteArray result;

	//type
	result.append(char(ClientT::MESSAGE));

	//message
	result.append(message);

	return result;
}

QString Parser::ParseAsMessage(QByteArray& data)
{
	return data.mid(1);                                      //whithout type
}



