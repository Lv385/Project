#include "info.h"
#include "friendinfo.h"

namespace SQLDAL {
FriendInfo::FriendInfo(std::shared_ptr<Connect> Connect):Info(Connect) {
  Connect_->Open(SERVER_DB);
}
FriendInfo::FriendInfo()
{
}
void FriendInfo::Add() {
  ExectuteQuery(AddQuery());
  query_.finish();
}

QVector<FriendInfo> FriendInfo::Get(const unsigned int id) {
  QVector<FriendInfo> result;
  ExectuteQuery(GetQuery(id));
  
  while (query_.next()) {
	  FriendInfo a(Connect_);
	  a.first_user_id = id;
	  a.second_user_id = query_.record().value(0).toUInt();

    result.push_back(a);
  }
  query_.finish();
  return result;
}

void FriendInfo::Delete() {
  ExectuteQuery(DeleteQuery());
  query_.finish();
}

QString FriendInfo::AddQuery() {
  return QString(
      "insert into friends (first_user_ID, second_user_ID) values (" +
      QString::number(first_user_id) + ", " + QString::number(second_user_id) + ")");
}

QString FriendInfo::GetQuery(const unsigned int id) {
  return QString("select second_user_id from friends where first_user_id = " +
                 QString::number(id));
}

QString FriendInfo::DeleteQuery() {
  return QString("delete from friends where first_user_ID = " +
                 QString::number(first_user_id) +
                 " and second_user_ID = " + QString::number(second_user_id));
}

}  // namespace SQLDAL