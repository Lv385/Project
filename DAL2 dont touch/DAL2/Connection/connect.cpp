#include "connect.h"
namespace SQLDAL {
	Connection::Connection(const QString& connection_name) {
		const QString driver_name = "QSQLITE";
		data_base_ = QSqlDatabase::addDatabase(driver_name, connection_name);
		connection_name_ = connection_name;
	}

	void Connection::Open(const QString& database_path) {
		data_base_.setDatabaseName(database_path);

		if (!data_base_.open()) {
			qDebug() << data_base_.lastError().text();
		}
		else {
			qDebug() << "success";
		}
	}

	void Connection::Close() {
		data_base_.close();
		data_base_.removeDatabase(connection_name_);
	}

	QSqlDatabase Connection::GetDB() { return data_base_; }
}