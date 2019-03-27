#include "requestinfo.h"

namespace SQLDAL {
	RequestInfo::RequestInfo(unsigned int f_id, unsigned int s_id, std::shared_ptr<Connect> Connect):Info(Connect)
	{
		first_user_id = f_id;
		second_user_id = s_id;
	}
	RequestInfo::RequestInfo(std::shared_ptr<Connect> Connect):Info(Connect) {
  Connect_->Open(SERVER_DB);
}
RequestInfo::RequestInfo()
{
}
void RequestInfo::Add() {
  ExectuteQuery(AddQuery());
  query_.finish();
}

QVector<RequestInfo> RequestInfo::Get(const unsigned int id) {
	QVector<RequestInfo> result;
	ExectuteQuery(GetQuery(id));

	while (query_.next()) {


		result.push_back(RequestInfo(query_.record().value(0).toUInt(),id, Connect_));
	}
	query_.finish();
	return result;
}

void RequestInfo::Delete() {
  ExectuteQuery(DeleteQuery());
  query_.finish();
}

QString RequestInfo::AddQuery() {
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

QString RequestInfo::DeleteQuery() {
  return QString("delete from friends_request where first_user_ID = " +
                 QString::number(first_user_id) +
                 " and second_user_ID = " + QString::number(second_user_id));
}

}  // namespace SQLDAL