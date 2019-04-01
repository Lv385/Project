#include "statement.h"
namespace SQLDAL {
Statement::Statement(std::shared_ptr<Connect> connection)
    : connection_(connection) {
  SetQuery(connection_->GetDB());
}

Statement::~Statement() { connection_->Close(); }

void Statement::SetQuery(QSqlDatabase database) {
  query_ = QSqlQuery(database);
}

void Statement::ExectuteQuery(QString query) {
  query_.prepare(query);
  if (!query_.exec()) {
    ErrorInfo();
  }
}

void Statement::ErrorInfo() {
  qDebug() << query_.lastError().databaseText();
  qDebug() << query_.lastError().driverText();
}
}  // namespace SQLDAL