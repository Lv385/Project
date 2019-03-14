#include "message.h"

Message::Message(const QString & connection_name) : ClientDAL(connection_name)
{
}

Message::Message()
{
}

QVector<Message> Message::GetMessages()
{
	ExectuteQuery(CreateQueryCountOfMessages());
	query_.first();
	unsigned int CountOfMessages = query_.value(0).toInt();
	QVector<Message> result(CountOfMessages);
	ExectuteQuery(CreateQuerySelectAll());
	int counter = 0;
	while (query_.next())
	{
		result[counter].id = query_.record().value(0).toInt();
		result[counter].chat_id = query_.record().value(1).toInt();
		result[counter].owner_id = query_.record().value(2).toInt();
		result[counter].data = query_.record().value(3).toString();
		result[counter].date = query_.record().value(4).toDate();
		result[counter].time = query_.record().value(5).toTime();
		result[counter++].status = query_.record().value(6).toInt();
	}
	return result;
}

void Message::AddNewMessage()
{
	ExectuteQuery(CreateQueryInsert());
	query_.finish();
}

QString Message::CreateQuerySelectAll()
{
	return QString("select* from Messages where user_ID = " + QString::number(chat_id));
}

QString Message::CreateQueryInsert()
{
	return QString("insert into Messages (user_ID, owner_ID, message_data, message_date, message_tima, message_status) values (" + QString::number(chat_id) + ", " + QString::number(owner_id) + ", '" + data + "', '" + date.toString() + "', '" + time.toString() + "', " + status + ")");
}

QString Message::CreateQueryUpdate()
{
	return QString("update message set ...");//..........is it necessary??
}

QString Message::CreateQueryDelete()
{
	return QString("delete from Messages where message_ID = "+QString::number(id));
}

QString Message::CreateQueryCountOfMessages()
{
	return QString("SELECT COUNT(user_ID) FROM Messages WHERE user_ID = "+QString::number(chat_id));
}
