#include "friendinfo.h"
#include "info.h"

namespace SQLDAL {
FriendInfo::FriendInfo(std::shared_ptr<Connect> Connect) : Info(Connect) {
  connection_->Open(SERVER_DB);
}
FriendInfo::FriendInfo() {}
void FriendInfo::Add(const UsersID& users_id) {
  ExectuteQuery(AddQuery(users_id));
  query_.finish();
}

QVector<UsersID> FriendInfo::Get(const unsigned int id) {
  QVector<UsersID> result;
  ExectuteQuery(GetQuery(id));

  while (query_.next()) {
    UsersID a;
    a.first_user_id = id;
    a.second_user_id = query_.record().value(0).toUInt();

    result.push_back(a);
  }
  query_.finish();
  return result;
}

void FriendInfo::Delete(const UsersID& users_id) {
  ExectuteQuery(DeleteQuery(users_id));
  query_.finish();
}

QString FriendInfo::AddQuery(const UsersID& users_id) {
  return QString(
      "insert into friends (first_user_ID, second_user_ID) values (" +
      QString::number(users_id.first_user_id) + ", " +
      QString::number(users_id.second_user_id) + ")");
}

QString FriendInfo::GetQuery(const unsigned int id) {
  return QString("select second_user_id from friends where first_user_id = " +
                 QString::number(id));
}

QString FriendInfo::DeleteQuery(const UsersID& users_id) {
  return QString(
      "delete from friends where first_user_ID = " +
      QString::number(users_id.first_user_id) +
      " and second_user_ID = " + QString::number(users_id.second_user_id));
}

}  // namespace SQLDAL