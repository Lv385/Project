#include "user.h"

User::User(const QString &connection_name) : ServerDAL(connection_name) {
  
}

void User::GetUser() {
  ExectuteQuery(CreateQuerySelect());
  query_.first();
  id = query_.value(0).toInt();
  login = query_.value(1).toString();
  password = query_.value(2).toString();
  ip = query_.value(3).toString();
  port = query_.value(4).toInt();

  query_.finish();
}

void User::UpdateUser() { 
  ExectuteQuery(CreateQueryUpdate()); 
  query_.finish();
}

void User::AddNewUser() { 
  ExectuteQuery(CreateQueryInsert());
  query_.finish();
}

void User::DeleteUser() {

  ExectuteQuery(CreateQueryDelete());
  query_.finish();
  query_.clear();
}

QString User::CreateQuerySelect() {
  return QString("select * from users where user_login = '" + login +
                 "' or user_id = " + QString::number(id));
  
}

QString User::CreateQueryInsert() {
  return QString(
      "insert into users (user_login, user_password, user_IP, user_port) "
      "values ('" +
      login + "', '" + password + "', '" + ip + "', " + QString::number(port) +
      ")");
}

QString User::CreateQueryUpdate() {
  return QString(
      "update users set user_password='" + password + "', user_IP = '" + ip +
      "', user_port = " + QString::number(port) + " where user_login = '" +
      login + "' or user_id = " + QString::number(id));
}

QString User::CreateQueryDelete() {
  return QString("delete from users where user_login = '" + login +
                 "' or user_id = " + QString::number(id));
}
