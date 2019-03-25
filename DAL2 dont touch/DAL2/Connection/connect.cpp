#include "connect.h"
namespace SQLDAL {
	Connect::Connect(const QString& Connect_name) {
		const QString driver_name = "QSQLITE";
		data_base_ = QSqlDatabase::addDatabase(driver_name, Connect_name);
		Connect_name_ = Connect_name;
	}

	void Connect::Open(const QString& database_path) {
		data_base_.setDatabaseName(database_path);

		if (!data_base_.open()) {
			qDebug() << data_base_.lastError().text();
		}
		else {
			qDebug() << "success";
		}
	}

	void Connect::Close() {
		data_base_.close();
		data_base_.removeDatabase(Connect_name_);
	}

	QSqlDatabase Connect::GetDB() { return data_base_; }
}