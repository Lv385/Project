#ifndef STATEMENT_H
#define STATEMENT_H

#include <qsqlrecord.h>
#include <QString>
#include <memory>
#include "connection.h"
#include "unitofwork.h"

#define CLIENT_DB "Client"
#define SERVER_DB "Server"

class Statement {
 public:
  Statement(std::shared_ptr<Connection> connection);
  Statement() = default;
  ~Statement();

  protected:
  virtual QString UpdateQuery() = 0;
  virtual QString SelectQuery() = 0;
  virtual QString InsertQuery() = 0;
  virtual QString DeleteQuery() = 0;

  void SetQuery(QSqlDatabase database);
  void ExectuteQuery(QString query);
  void ErrorInfo();

  std::shared_ptr<Connection> connection_;
  QSqlQuery query_;
};

#endif  // !STATEMENT_H
