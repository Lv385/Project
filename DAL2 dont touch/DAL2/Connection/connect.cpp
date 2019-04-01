#include "connect.h"
namespace SQLDAL {
Connect::Connect(const QString& connection_name)
    : connection_name_(connection_name) {
  const QString driver_name = "QSQLITE";
  data_base_ = QSqlDatabase::addDatabase(driver_name, connection_name);
}

void Connect::Open(const QString& database_path) {
  data_base_.setDatabaseName(database_path);

  if (!data_base_.open()) {
    qDebug() << data_base_.lastError().text();
  } else {
    qDebug() << "success";
  }
}

void Connect::Close() {
  data_base_.close();
  data_base_.removeDatabase(connection_name_);
}

QSqlDatabase Connect::GetDB() { return data_base_; }
}  // namespace SQLDAL