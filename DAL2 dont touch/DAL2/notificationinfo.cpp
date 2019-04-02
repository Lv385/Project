#include "notificationinfo.h"
namespace SQLDAL {
	SQLDAL::NotificationInfo::NotificationInfo(std::shared_ptr<Connect> Connect) :Info(Connect) {
		connection_->Open(SERVER_DB);
	}

	SQLDAL::NotificationInfo::NotificationInfo()
	{
	}

	void SQLDAL::NotificationInfo::Add(const UsersID& users_id) {
		ExectuteQuery(AddQuery(users_id));
		query_.finish();
	}

	QVector<UsersID> SQLDAL::NotificationInfo::Get(const unsigned int id) {
		QVector<UsersID> result;
		ExectuteQuery(GetQuery(id));

		while (query_.next()) {
			UsersID a;
			a.second_user_id = id;
			a.first_user_id = query_.record().value(0).toUInt();

			result.push_back(a);
		}
		query_.finish();
		return result;
	}

	void SQLDAL::NotificationInfo::Delete(const UsersID& users_id) {
		ExectuteQuery(DeleteQuery(users_id));
		query_.finish();
	}

	QString SQLDAL::NotificationInfo::AddQuery(const UsersID& users_id) {
		return QString(
			"insert into friends_notification (first_user_ID, second_user_ID) values (" +
			QString::number(users_id.first_user_id) + ", " + QString::number(users_id.second_user_id) +
			")");
	}

	QString SQLDAL::NotificationInfo::GetQuery(const unsigned int id) {
		return QString(
			"select first_user_id from friends_notification where second_user_id = " +
			QString::number(id));
	}

	QString SQLDAL::NotificationInfo::DeleteQuery(const UsersID& users_id) {
		return QString("delete from friends_notification where first_user_ID = " +
			QString::number(users_id.first_user_id) +
			" and second_user_ID = " + QString::number(users_id.second_user_id));
	}
}