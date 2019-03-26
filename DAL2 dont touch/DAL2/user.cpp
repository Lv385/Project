#include "user.h"
namespace SQLDAL {
User::User(std::shared_ptr<Connect> Connect) : Statement(Connect) {
  Connect_->Open(SERVER_DB);  // Path
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