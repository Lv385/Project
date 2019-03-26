#include "info.h"
#include "friendinfo.h"

namespace SQLDAL {
void FriendInfo::Add(const unsigned int first_user_id,
                     const unsigned int second_user_id) {
  ExectuteQuery(AddQuery(first_user_id, second_user_id));
  query_.finish();
}

QVector<unsigned int> FriendInfo::Get(const unsigned int id) {
  QVector<unsigned int> result;
  ExectuteQuery(GetQuery(id));
  
  while (query_.next()) {
    result.push_back(query_.record().value(0).toUInt());
  }
  query_.finish();
  return result;
}

void FriendInfo::Delete(const unsigned int first_user_id,
                        const unsigned int second_user_id) {
  ExectuteQuery(DeleteQuery(first_user_id,second_user_id));
  query_.finish();
}

QString FriendInfo::AddQuery(const unsigned int first_user_id,
                             const unsigned int second_user_id) {
  return QString(
      "insert into friends (first_user_ID, second_user_ID) values (" +
      QString::number(first_user_id) + ", " + QString::number(second_user_id) + ")");
}

QString FriendInfo::GetQuery(const unsigned int id) {
  return QString("select second_user_id from friends where first_user_id = " +
                 QString::number(id));
}

QString FriendInfo::DeleteQuery(const unsigned int first_user_id,
                                const unsigned int second_user_id) {
  return QString("delete from friends where first_user_ID = " +
                 QString::number(first_user_id) +
                 " and second_user_ID = " + QString::number(second_user_id));
}

}  // namespace SQLDAL