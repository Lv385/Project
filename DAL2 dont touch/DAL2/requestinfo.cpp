#include "requestinfo.h"

namespace SQLDAL {
RequestInfo::RequestInfo(std::shared_ptr<Connect> Connect) {
  Connect_->Open(SERVER_DB);
}
void RequestInfo::Add(const unsigned int first_user_id,
                     const unsigned int second_user_id) {
  ExectuteQuery(AddQuery(first_user_id, second_user_id));
  query_.finish();
}

QVector<unsigned int> RequestInfo::Get(const unsigned int id) {
  QVector<unsigned int> result;
  ExectuteQuery(GetQuery(id));

  while (query_.next()) {
    result.push_back(query_.record().value(0).toUInt());
  }
  query_.finish();
  return result;
}

void RequestInfo::Delete(const unsigned int first_user_id,
                        const unsigned int second_user_id) {
  ExectuteQuery(DeleteQuery(first_user_id, second_user_id));
  query_.finish();
}

QString RequestInfo::AddQuery(const unsigned int first_user_id,
                             const unsigned int second_user_id) {
  return QString(
      "insert into friends_request (first_user_ID, second_user_ID) values (" +
      QString::number(first_user_id) + ", " + QString::number(second_user_id) +
      ")");
}

QString RequestInfo::GetQuery(const unsigned int id) {
  return QString(
      "select first_user_id from friends_request where second_user_id = " +
      QString::number(id));
}

QString RequestInfo::DeleteQuery(const unsigned int first_user_id,
                                const unsigned int second_user_id) {
  return QString("delete from friends_request where first_user_ID = " +
                 QString::number(first_user_id) +
                 " and second_user_ID = " + QString::number(second_user_id));
}

}  // namespace SQLDAL