#include "notificationinfo.h"
namespace SQLDAL {
	SQLDAL::NotificationInfo::NotificationInfo(std::shared_ptr<Connect> Connect) :Info(Connect) {
		Connect_->Open(SERVER_DB);
	}

	SQLDAL::NotificationInfo::NotificationInfo()
	{
	}

	void SQLDAL::NotificationInfo::Add() {
		ExectuteQuery(AddQuery());
		query_.finish();
	}

	QVector<NotificationInfo> SQLDAL::NotificationInfo::Get(const unsigned int id) {
		QVector<NotificationInfo> result;
		ExectuteQuery(GetQuery(id));

		while (query_.next()) {
			NotificationInfo a(Connect_);
			a.second_user_id = id;
			a.first_user_id = query_.record().value(0).toUInt();

			result.push_back(a);
		}
		query_.finish();
		return result;
	}

	void SQLDAL::NotificationInfo::Delete() {
		ExectuteQuery(DeleteQuery());
		query_.finish();
	}

	QString SQLDAL::NotificationInfo::AddQuery() {
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

	QString SQLDAL::NotificationInfo::DeleteQuery() {
		return QString("delete from friends_notification where first_user_ID = " +
			QString::number(first_user_id) +
			" and second_user_ID = " + QString::number(second_user_id));
	}
}