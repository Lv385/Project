#ifndef STATEMENT_H
#define STATEMENT_H

#include <qsqlrecord.h>
#include <QString>
#include <memory>
#include "connection.h"
#include "unitofwork.h"

#define CLIENT_DB "../DAL2 dont touch/DAL2/Client"
#define SERVER_DB "../DAL2 dont touch/DAL2/Server"

class Statement {
 public:
  Statement(std::shared_ptr<Connection> connection);
  Statement() = default;
  ~Statement();

  protected:


  void SetQuery(QSqlDatabase database);
  void ExectuteQuery(QString query);
  void ErrorInfo();

  std::shared_ptr<Connection> connection_;
  QSqlQuery query_;
};

#endif  // !STATEMENT_H
