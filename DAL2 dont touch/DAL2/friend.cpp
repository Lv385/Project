#include "friend.h"

Friend::Friend(const QString & connection_name) : ClientDAL(connection_name)
{
}

Friend::Friend()
{
}

QVector<Friend> Friend::GetFriends()
{
	ExectuteQuery(CreateQueryCountOfFriends());
	query_.first();
	unsigned int CountOfFriends = query_.value(0).toInt();
	QVector<Friend> result(CountOfFriends);
	ExectuteQuery(CreateQuerySelectAll());
	int counter = 0;
	while (query_.next())
	{
		result[counter].id = query_.record().value(0).toInt();
		result[counter].name = query_.record().value(1).toString();
		result[counter].surname = query_.record().value(2).toString();
		result[counter].ip = query_.record().value(3).toString();
		result[counter].port = query_.record().value(4).toInt();
		result[counter].login = query_.record().value(5).toString();
		result[counter++].status = query_.record().value(6).toBool();
	}
	return result;
}

QString Friend::CreateQuerySelectAll()
{
	return QString("SELECT friends.user_id ,friend_info.user_name , friend_info.user_surname ,  friends.user_IP , friends.user_port , friends.user_login ,friends.user_status FROM friend_info JOIN friends ON friend_info.user_ID = friends.user_id; ");
}

QString Friend::CreateQueryInsert()
{
	return QString("insert into ...\ninsert into");//create one table friends
}

QString Friend::CreateQueryCountOfFriends()
{
	return QString("SELECT COUNT(user_id) FROM friends");
}
