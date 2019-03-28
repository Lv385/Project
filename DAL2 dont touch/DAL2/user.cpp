#include "user.h"
namespace SQLDAL {
	User::User(std::shared_ptr<Connect> Connect) : Statement(Connect) {
		Connect_->Open(SERVER_DB);  // Path
		friend_obj = std::make_shared<FriendInfo>(Connect);
		request_obj = std::make_shared<RequestInfo>(Connect);
		notification_obj = std::make_shared<NotificationInfo>(Connect);

	}

	User::~User() {}

	void User::GetUser() {
		ExectuteQuery(SelectQuery());
		query_.first();
		id = query_.value(0).toInt();
		login = query_.value(1).toString();
		password = query_.value(2).toString();
		ip = query_.value(3).toString();
		port = query_.value(4).toInt();

		query_.finish();
		GetFriends();
		GetFriendsRequest();
		GetFriendsNotification();
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
	}

	void User::GetFriends()
	{
		friends = friend_obj->Get(id);

	}

	void User::GetFriendsRequest()
	{
		requests = request_obj->Get(id);
	}

	void User::GetFriendsNotification()
	{
		notification = notification_obj->Get(id);
	}

	void User::AddFriend(unsigned int user_id)
	{
		UsersID users_id;
		users_id.first_user_id = id;
		users_id.second_user_id = user_id;
		friend_obj->Add(users_id);
		GetFriends();
	}

	void User::AddFriendRequest(unsigned int user_id)
	{
		UsersID users_id;
		users_id.second_user_id = id;
		users_id.first_user_id = user_id;
		request_obj->Add(users_id);
		GetFriendsRequest();
	}

	void User::AddFriendNotification(unsigned int user_id)
	{
		UsersID users_id;
		users_id.second_user_id = id;
		users_id.first_user_id = user_id;
		notification_obj->Add(users_id);
		GetFriendsNotification();
	}

	void User::DeleteFriend(unsigned int user_id)
	{
		UsersID users_id;
		users_id.first_user_id = id;
		users_id.second_user_id = user_id;
		friend_obj->Delete(users_id);
		GetFriends();
	}

	void User::DeleteFriendRequest(unsigned int user_id)
	{
		UsersID users_id;
		users_id.second_user_id = id;
		users_id.first_user_id = user_id;
		request_obj->Delete(users_id);
		GetFriendsRequest();
	}

	void User::DeleteFriendNotification(unsigned int user_id)
	{
		UsersID users_id;
		users_id.second_user_id = id;
		users_id.first_user_id = user_id;
		notification_obj->Delete(users_id);
		GetFriendsNotification();
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

	QString User::CountOfFriendsRequest() {
		return QString(
			"SELECT COUNT(second_user_id) FROM friends_request where second_user_id "
			"= " +
			QString::number(id));
	}
}  // namespace SQLDAL