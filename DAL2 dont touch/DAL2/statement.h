#ifndef STATEMENT_H
#define STATEMENT_H

#include "connection.h"


class Statement {
 public:
  //Statement(const QString &connection_name);
  Statement();
  ~Statement();

//protected:
  void SetQuery(QSqlDatabase database);
  void ExectuteQuery(QString query);
  void ErrorInfo();
  QSqlQuery query_;
};	

#endif  // !STATEMENT_H
