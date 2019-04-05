#include "requestinfo.h"

namespace dal {
RequestInfo::RequestInfo(std::shared_ptr<Connect> Connect) : Info(Connect) {
  connection_->Open(SERVER_DB);
}
RequestInfo::RequestInfo() {}
void RequestInfo::Add(const UsersID& users_id) {
  ExectuteQuery(AddQuery(users_id));
  query_.finish();
}

QVector<UsersID> RequestInfo::Get(const unsigned int id) {
  QVector<UsersID> result;
  ExectuteQuery(GetQuery(id));
  UsersID user_ids;
  user_ids.second_user_id = id;
  while (query_.next()) {
	user_ids.first_user_id = query_.record().value(0).toUInt();
    result.push_back(user_ids);
  }
  query_.finish();
  return result;
}

void RequestInfo::Delete(const UsersID& users_id) {
  ExectuteQuery(DeleteQuery(users_id));
  query_.finish();
}

QString RequestInfo::AddQuery(const UsersID& users_id) {
  return QString(
      "insert into friends_request (first_user_ID, second_user_ID) values (" +
      QString::number(users_id.first_user_id) + ", " +
      QString::number(users_id.second_user_id) + ")");
}

QString RequestInfo::GetQuery(const unsigned int id) {
  return QString(
      "select first_user_id from friends_request where second_user_id = " +
      QString::number(id));
}

QString RequestInfo::DeleteQuery(const UsersID& users_id) {
  return QString(
      "delete from friends_request where first_user_ID = " +
      QString::number(users_id.first_user_id) +
      " and second_user_ID = " + QString::number(users_id.second_user_id));
}

}  // namespace dal