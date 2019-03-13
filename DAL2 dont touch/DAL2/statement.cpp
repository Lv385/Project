#include "statement.h"

/*Statement::Statement(const QString &connection_name)
    : Connection(connection_name) {
  Open("das");
}*/

Statement::Statement() {}

Statement::~Statement() {}

void Statement::SetQuery(QSqlDatabase database) {
  query_ = QSqlQuery(database);
}

void Statement::ExectuteQuery(QString query) {
  //query_ = QSqlQuery(data_base_);
  query_.prepare(query);
  if (!query_.exec()) {
    ErrorInfo();
  }
}

void Statement::ErrorInfo() {
  qDebug() << query_.lastError().databaseText();
  qDebug() << query_.lastError().driverText();
}
