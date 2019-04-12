#include "user.h"
namespace SQLDAL {
Users::Users(std::shared_ptr<Connect> Connect) : Statement(Connect) {
  connection_->Open(SERVER_DB);  // Path
  friend_obj = std::make_shared<FriendInfo>(Connect);
  request_obj = std::make_shared<RequestInfo>(Connect);
  notification_obj = std::make_shared<NotificationInfo>(Connect);
}

	Users::~Users() {}

	User Users::GetUser(const unsigned int& user_id) {
		ExectuteQuery(SelectQuery(user_id));
		query_.first();
		User user;
		user.id = query_.value(0).toInt();
		user.login = query_.value(1).toString();
		user.password = query_.value(2).toString();
		user.ip = query_.value(3).toString();
		user.port = query_.value(4).toInt();
		query_.finish();
		user.notification = GetFriendsNotification(user.id);
		user.friends = GetFriends(user.id);
		user.requests = GetFriendsRequest(user.id);
		
		return user;

	}

	User Users::GetUser(const QString& user_login) {
		ExectuteQuery(SelectQuery(user_login));
		query_.first();
		User user{};
		user.id = query_.value(0).toInt();
		user.login = query_.value(1).toString();
		user.password = query_.value(2).toString();
		user.ip = query_.value(3).toString();
		user.port = query_.value(4).toInt();
		query_.finish();
		user.friends = GetFriends(user.id);
		user.requests = GetFriendsRequest(user.id);
		user.notification = GetFriendsNotification(user.id);

		return user;
	}

void Users::UpdateUser(const User& user) {
  ExectuteQuery(UpdateQuery(user));
  query_.finish();

}

void Users::AddNewUser(const User& user) {
  ExectuteQuery(InsertQuery(user));
  query_.finish();


}

void Users::DeleteUser(const User& user) {
  ExectuteQuery(DeleteQuery(user));
  query_.finish();
}

QVector<UsersID> Users::GetFriends(const unsigned int id) {
	return friend_obj->Get(id);
}

QVector<UsersID> Users::GetFriendsRequest(const unsigned int id){
	return request_obj->Get(id);
}

QVector<UsersID> Users::GetFriendsNotification(const unsigned int id) {
  return notification_obj->Get(id);
}

void Users::AddFriend(const UsersID& ids) {

  friend_obj->Add(ids);
}

void Users::AddFriendRequest(const UsersID& ids) {
  request_obj->Add(ids);
}

void Users::AddFriendNotification(const UsersID& ids) {
  notification_obj->Add(ids);
}

void Users::DeleteFriend(const UsersID& ids) {
  friend_obj->Delete(ids);
}

void Users::DeleteFriendRequest(const UsersID& ids) {
  request_obj->Delete(ids);
}

void Users::DeleteFriendNotification(const UsersID& ids) {
  notification_obj->Delete(ids);
}

QString Users::SelectQuery(unsigned int user_id) {
	return QString("select * from users where user_id = " + QString::number(user_id));
}
QString Users::SelectQuery(QString user_login) {
	return QString("select * from users where user_login = '" + user_login + "'");
}

QString Users::InsertQuery(User user) {
  return QString(
      "insert into users (user_login, user_password, user_IP, user_port) "
      "values ('" +
	  user.login + "', '" + user.password + "', '" + user.ip + "', " + QString::number(user.port) +
      ")");
}

QString Users::UpdateQuery(User user) {
  return QString(
      "update users set user_password='" + user.password + "', user_IP = '" + user.ip +
      "', user_port = " + QString::number(user.port) + " where user_login = '" +
	  user.login + "' or user_id = " + QString::number(user.id));
}

QString Users::DeleteQuery(User user) {
  return QString("delete from users where user_login = '" + user.login +
                 "' or user_id = " + QString::number(user.id));
}


}  // namespace SQLDAL
