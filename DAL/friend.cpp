#include "friend.h"
namespace dal {
Friends::Friends(std::shared_ptr<Connect> Connect) : Statement(Connect) {
  connection_->Open(CLIENT_DB);
}

Friends::Friends() : Statement() {}

QVector<Friend> Friends::GetFriends() {
  ExectuteQuery(CreateQueryCountOfFriends());
  query_.first();
  unsigned int count_of_friends = query_.value(0).toInt();
  QVector<Friend> friends(count_of_friends);
  ExectuteQuery(CreateQuerySelectAll());
  unsigned int counter = 0;
  while (query_.next()) {
	  FillStructure(friends[counter]);
	  counter++;
  }
  return friends;
}

Friend Friends::GetFriend(const unsigned int id) {
  ExectuteQuery(SelectQuery(id));
  query_.first();
  Friend _friend;
  FillStructure(_friend);

  query_.finish();
  return _friend;
}

Friend Friends::GetFriend(const QString & login)
{
	ExectuteQuery(SelectQuery(login));
	query_.first();
	Friend _friend;
	FillStructure(_friend);

	query_.finish();
	return _friend;
}

void Friends::UpdateFriend(const Friend& _friend) {
  ExectuteQuery(UpdateQuery(_friend));
  query_.finish();
}

void Friends::AddNewFriend(const Friend& _friend) {
  ExectuteQuery(InsertQuery(_friend));
  query_.finish();
}

void Friends::DeleteFriend(const Friend& _friend) {
  ExectuteQuery(DeleteQuery(_friend));
  query_.finish();
}

void Friends::FillStructure(Friend & _friend)
{
	_friend.id = query_.value(0).toInt();
	_friend.name = query_.value(1).toString();
	_friend.surname = query_.value(2).toString();
	_friend.ip = query_.value(3).toString();
	_friend.port = query_.value(4).toInt();
	_friend.login = query_.value(5).toString();
	_friend.status = query_.value(6).toBool();
	
}

QString Friends::CreateQuerySelectAll() {
  return QString(
      "SELECT user_id, user_name, user_surname,  user_IP, user_port, "
      "user_login, user_status FROM friends");
}

QString Friends::UpdateQuery(const Friend& _friend) {
  return QString("update friends set user_name = '" + _friend.name +
                 "', user_surname= '" + _friend.surname + "',  user_IP= '" +
                 _friend.ip + "', user_port= " + QString::number(_friend.port) +
                 ", user_status= '" + QString::number(_friend.status) +
                 "' where user_id = " + QString::number(_friend.id) +
                 " or user_login = '" + _friend.login + "'");
}

QString Friends::SelectQuery(const unsigned int id) {
  return QString(
      "SELECT user_id, user_name, user_surname,  user_IP, user_port, "
      "user_login, user_status FROM friends where user_id = " +
      QString::number(id));
}

QString Friends::SelectQuery(const QString & login)
{
	return QString(
		"SELECT user_id, user_name, user_surname,  user_IP, user_port, "
		"user_login, user_status FROM friends where  user_login = '" + login + "'");
}

QString Friends::InsertQuery(const Friend& _friend) {
  return QString(
      "insert into friends "
      "(user_id,user_IP,user_port,user_login,user_status,user_name,user_"
      "surname) values (" +
      QString::number(_friend.id) + ", '" + _friend.ip + "', " +
      QString::number(_friend.port) + ", '" + _friend.login + "', " +
      QString::number(_friend.status) + ", '" + _friend.name + "', '" +
      _friend.surname + "')");
}

QString Friends::DeleteQuery(const Friend& _friend) {
  return QString(
      "delete from friends where user_id = " + QString::number(_friend.id) +
      " or user_login = '" + _friend.login + "'");
}

QString Friends::CreateQueryCountOfFriends() {
  return QString("SELECT COUNT(user_id) FROM friends");
}
}  // namespace dal
