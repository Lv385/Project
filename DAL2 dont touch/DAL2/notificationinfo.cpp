#include "notificationinfo.h"

SQLDAL::NotificationInfo::NotificationInfo(std::shared_ptr<Connect> Connect) {
  Connect_->Open(SERVER_DB);
}

void SQLDAL::NotificationInfo::Add(const unsigned int first_user_id,
                                   const unsigned int second_user_id) {
  ExectuteQuery(AddQuery(first_user_id, second_user_id));
  query_.finish();
}

QVector<unsigned int> SQLDAL::NotificationInfo::Get(const unsigned int id) {
  QVector<unsigned int> result;
  ExectuteQuery(GetQuery(id));

  while (query_.next()) {
    result.push_back(query_.record().value(0).toUInt());
  }
  query_.finish();
  return result;
}

void SQLDAL::NotificationInfo::Delete(const unsigned int first_user_id,
                                      const unsigned int second_user_id) {
  ExectuteQuery(DeleteQuery(first_user_id, second_user_id));
  query_.finish();
}

QString SQLDAL::NotificationInfo::AddQuery(const unsigned int first_user_id,
                                           const unsigned int second_user_id) {
  return QString(
      "insert into friends_notification (first_user_ID, second_user_ID) values (" +
      QString::number(first_user_id) + ", " + QString::number(second_user_id) +
      ")");
}

QString SQLDAL::NotificationInfo::GetQuery(const unsigned int id) {
  return QString(
      "select first_user_id from friends_notification where second_user_id = " +
      QString::number(id));
}

QString SQLDAL::NotificationInfo::DeleteQuery(
    const unsigned int first_user_id, const unsigned int second_user_id) {
  return QString("delete from friends_notification where first_user_ID = " +
                 QString::number(first_user_id) +
                 " and second_user_ID = " + QString::number(second_user_id));
}
