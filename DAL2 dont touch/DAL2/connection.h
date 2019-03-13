#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QDebug>

class Connection {
 public:
  explicit Connection(const QString &connection_name,
                      const QString &driver_name = "QSQLITE");
  void Open(const QString &database_path);
  void Close();
  //bool IsOpen() const;
  QSqlDatabase GetDB();
 private:
  QSqlDatabase data_base_;
  QString connection_name_;
};

#endif  // !CONNECTION_H

