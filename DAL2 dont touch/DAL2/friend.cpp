#include "friend.h"
namespace SQLDAL {
Friend::Friend(std::shared_ptr<Connect> Connect) : Statement(Connect) {
  connection_->Open(CLIENT_DB);
}

Friend::Friend() : Statement() {}

QVector<Friends> Friend::GetFriends() {
  ExectuteQuery(CreateQueryCountOfFriends());
  query_.first();
  unsigned int count_of_friends = query_.value(0).toInt();
  QVector<Friends> friends(count_of_friends);
  ExectuteQuery(CreateQuerySelectAll());
  unsigned int counter = 0;
  while (query_.next()) {
    friends[counter].id = query_.record().value(0).toInt();
    friends[counter].name = query_.record().value(1).toString();
    friends[counter].surname = query_.record().value(2).toString();
    friends[counter].ip = query_.record().value(3).toString();
    friends[counter].port = query_.record().value(4).toInt();
    friends[counter].login = query_.record().value(5).toString();
    friends[counter++].status = query_.record().value(6).toBool();
  }
  return friends;
}

Friends Friend::GetFriend(const unsigned int id) {
  ExectuteQuery(SelectQuery(id));
  query_.first();
  Friends _friend;
  _friend.id = query_.value(0).toInt();
  _friend.name = query_.value(1).toString();
  _friend.surname = query_.value(2).toString();
  _friend.ip = query_.value(3).toString();
  _friend.port = query_.value(4).toInt();
  _friend.login = query_.value(5).toString();
  _friend.status = query_.value(6).toBool();

  query_.finish();
  return _friend;
}

void Friend::UpdateFriend(const Friends& _friend) {
  ExectuteQuery(UpdateQuery(_friend));
  query_.finish();
}

void Friend::AddNewFriend(const Friends& _friend) {
  ExectuteQuery(InsertQuery(_friend));
  query_.finish();
}

void Friend::DeleteFriend(const Friends& _friend) {
  ExectuteQuery(DeleteQuery(_friend));
  query_.finish();
}

QString Friend::CreateQuerySelectAll() {
  return QString(
      "SELECT user_id, user_name, user_surname,  user_IP, user_port, "
      "user_login, user_status FROM friends");
}

QString Friend::UpdateQuery(const Friends& _friend) {
  return QString("update friends set user_name = '" + _friend.name +
                 "', user_surname= '" + _friend.surname + "',  user_IP= '" +
                 _friend.ip + "', user_port= " + QString::number(_friend.port) +
                 ", user_status= '" + QString::number(_friend.status) +
                 "' where user_id = " + QString::number(_friend.id) +
                 " or user_login = '" + _friend.login + "'");
}

QString Friend::SelectQuery(const unsigned int id) {
  return QString(
      "SELECT user_id, user_name, user_surname,  user_IP, user_port, "
      "user_login, user_status FROM friends where user_id = " +
      QString::number(id));  // + " or user_login = '" + login + "'");
}

QString Friend::InsertQuery(const Friends& _friend) {
  return QString(
      "insert into friends "
      "(user_id,user_IP,user_port,user_login,user_status,user_name,user_"
      "surname) values (" +
      QString::number(_friend.id) + ", '" + _friend.ip + "', " +
      QString::number(_friend.port) + ", '" + _friend.login + "', " +
      QString::number(_friend.status) + ", '" + _friend.name + "', '" +
      _friend.surname + "')");
}

QString Friend::DeleteQuery(const Friends& _friend) {
  return QString(
      "delete from friends where user_id = " + QString::number(_friend.id) +
      " or user_login = '" + _friend.login + "'");
}

QString Friend::CreateQueryCountOfFriends() {
  return QString("SELECT COUNT(user_id) FROM friends");
}
}  // namespace SQLDAL
