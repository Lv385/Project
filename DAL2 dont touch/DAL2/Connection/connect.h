#ifndef CONNECTION_H
#define CONNECTION_H

#include <QDebug>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>

namespace SQLDAL {
	class Connection {
	public:
		explicit		Connection(const QString &connection_name);
		void			Open(const QString &database_path);
		void			Close();
		QSqlDatabase  GetDB();

	private:
		QSqlDatabase	data_base_;
		QString		connection_name_;
	};
}
#endif  // !CONNECTION_H
