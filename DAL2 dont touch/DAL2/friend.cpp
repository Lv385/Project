#include "friend.h"
namespace SQLDAL {
	Friend::Friend(std::shared_ptr<Connect> Connect) : Statement(Connect) {
		Connect_->Open(CLIENT_DB);
	}

	Friend::Friend() : Statement() {}

	QVector<Friend> Friend::GetFriends() {
		ExectuteQuery(CreateQueryCountOfFriends());
		query_.first();
		unsigned int CountOfFriends = query_.value(0).toInt();
		QVector<Friend> result(CountOfFriends);
		ExectuteQuery(CreateQuerySelectAll());
		int counter = 0;
		while (query_.next()) {
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

	void Friend::GetFriend() {
		ExectuteQuery(SelectQuery());
		query_.first();
		id = query_.value(0).toInt();
		name = query_.value(1).toString();
		surname = query_.value(2).toString();
		ip = query_.value(3).toString();
		port = query_.value(4).toInt();
		login = query_.value(5).toString();
		status = query_.value(6).toBool();

		query_.finish();
	}

	void Friend::UpdateFriend() {
		ExectuteQuery(UpdateQuery());
		query_.finish();
	}

	void Friend::AddNewFriend() {
		ExectuteQuery(InsertQuery());
		query_.finish();
	}

	void Friend::DeleteFriend() {
		ExectuteQuery(DeleteQuery());
		query_.finish();
	}

	QString Friend::CreateQuerySelectAll() {
		return QString(
			"SELECT user_id, user_name, user_surname,  user_IP, user_port, "
			"user_login, user_status FROM friends");
	}

	QString Friend::UpdateQuery() {
		return QString("update friends set user_name = '" + name +
			"', user_surname= '" + surname + "',  user_IP= '" + ip +
			"', user_port= " + QString::number(port) + ", user_status= '" +
			QString::number(status) + "' where user_id = " +
			QString::number(id) + " or user_login = '" + login + "'");
	}

	QString Friend::SelectQuery() {
		return QString(
			"SELECT user_id, user_name, user_surname,  user_IP, user_port, "
			"user_login, user_status FROM friends where user_id = " +
              QString::number(id) + " or user_login = '" + login +
              "' or (user_IP = '" + ip +
              "' and user_port = " + QString::number(port) + ")");
	}

	QString Friend::InsertQuery() {
		return QString(
			"insert into friends "
			"(user_id,user_IP,user_port,user_login,user_status,user_name,user_"
			"surname) values (" +
			QString::number(id) + ", '" + ip + "', " + QString::number(port) + ", '" +
			login + "', " + QString::number(status) + ", '" + name + "', '" +
			surname + "')");
	}

	QString Friend::DeleteQuery() {
		return QString("delete from friends where user_id = " + QString::number(id) +
			" or user_login = '" + login + "'");
	}

	QString Friend::CreateQueryCountOfFriends() {
		return QString("SELECT COUNT(user_id) FROM friends");
	}
}