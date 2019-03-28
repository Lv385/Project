#include "user.h"
namespace SQLDAL {
	User::User(std::shared_ptr<Connect> Connect) : Statement(Connect) {
		Connect_->Open(SERVER_DB);  // Path
	}

	User::~User() {}

	void User::AddNewFriend(const unsigned int & friend_id)
	{
		ExectuteQuery(InsertFriendQuery(friend_id));
		query_.finish();
	}

	QVector<int> User::GetFriends() {
		ExectuteQuery(CountOfFriends());
		query_.first();
		unsigned int CountOfFriends = query_.value(0).toInt();
		QVector<int> result(CountOfFriends);
		ExectuteQuery(SelectFriendsQuery());
		int counter = 0;
		while (query_.next()) {
			result[counter++] = query_.record().value(0).toInt();
		}
		return result;
	}

	void User::DeleteFriend(const unsigned int & friend_id)
	{
		ExectuteQuery(DeleteFriendQuery(friend_id));
		query_.finish();
	}

	void User::AddNewFriendRequest(const unsigned int & friend_id)
	{
		ExectuteQuery(InsertFriendRequestQuery(friend_id));
		query_.finish();
	}

	QVector<int> User::GetFriendsRequest()
	{
		ExectuteQuery(CountOfFriendsRequest());
		query_.first();
		unsigned int CountOfFriendsRequest = query_.value(0).toInt();
		QVector<int> result(CountOfFriendsRequest);
		ExectuteQuery(SelectFriendsRequestQuery());
		int counter = 0;
		while (query_.next()) {
			result[counter++] = query_.record().value(0).toInt();
		}
		return result;
	}

	void User::DeleteFriendRequest(const unsigned int & friend_id)
	{
		ExectuteQuery(DeleteFriendRequestQuery(friend_id));
		query_.finish();
	}

	void User::GetUser() {
		ExectuteQuery(SelectQuery());
		query_.first();
		id = query_.value(0).toInt();
		login = query_.value(1).toString();
		password = query_.value(2).toString();
		ip = query_.value(3).toString();
		port = query_.value(4).toInt();

		query_.finish();
	}

	void User::UpdateUser() {
		ExectuteQuery(UpdateQuery());
		query_.finish();
	}

	void User::AddNewUser() {
		ExectuteQuery(InsertQuery());
		query_.finish();
	}

	void User::DeleteUser() {
		ExectuteQuery(DeleteQuery());
		query_.finish();
		// query_.clear();
	}

	QString User::SelectQuery() {
		return QString("select * from users where user_login = '" + login +
			"' or user_id = " + QString::number(id));
	}

	QString User::InsertQuery() {
		return QString(
			"insert into users (user_login, user_password, user_IP, user_port) "
			"values ('" +
			login + "', '" + password + "', '" + ip + "', " + QString::number(port) +
			")");
	}

	QString User::InsertFriendQuery(unsigned int friend_id)
	{
		return QString("insert into friends (first_user_ID, second_user_ID) values (" + QString::number(id) + ", " + QString::number(friend_id) + ")");
	}

	QString User::SelectFriendsQuery() {
		return QString("select second_user_id from friends where first_user_id = " +
			QString::number(id));
	}

	QString User::DeleteFriendQuery(const unsigned int & friend_id)
	{
		return QString("delete from friends where first_user_ID = " + QString::number(id) + " and second_user_ID = " + QString::number(friend_id));
	}

	QString User::InsertFriendRequestQuery(unsigned int friend_id)
	{
		return QString("insert into friends_request (first_user_ID, second_user_ID) values (" + QString::number(id) + ", " + QString::number(friend_id) + ")");
	}

	QString User::SelectFriendsRequestQuery()
	{
		return QString("select first_user_id from friends_request where second_user_id = " +
			QString::number(id));
	}

	QString User::DeleteFriendRequestQuery(const unsigned int & friend_id)
	{
		return QString("delete from friends_request where first_user_ID = " + QString::number(id) + " and second_user_ID = " + QString::number(friend_id));
	}

	QString User::UpdateQuery() {
		return QString(
			"update users set user_password='" + password + "', user_IP = '" + ip +
			"', user_port = " + QString::number(port) + " where user_login = '" +
			login + "' or user_id = " + QString::number(id));
	}

	QString User::DeleteQuery() {
		return QString("delete from users where user_login = '" + login +
			"' or user_id = " + QString::number(id));
	}

	QString User::CountOfFriends() {
		return QString(
			"SELECT COUNT(first_user_id) FROM friends where first_user_id = " +
			QString::number(id));
	}

	QString User::CountOfFriendsRequest()
	{
		return QString(
			"SELECT COUNT(second_user_id) FROM friends_request where second_user_id = " +
			QString::number(id));
	}
}