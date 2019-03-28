#ifndef Connect_H
#define Connect_H

#include <QDebug>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>

namespace SQLDAL {
  class Connect {
  public:
	  explicit		Connect(const QString &connection_name);
	  void			Open(const QString &database_path);
	  void			Close();
	  QSqlDatabase    GetDB();

  private:
	  QSqlDatabase	data_base_;
	  QString		    connection_name_;
  };
}
#endif  // !Connect_H
