#ifndef STATEMENT_H
#define STATEMENT_H

#include <qsqlrecord.h>
#include <QString>
#include <memory>
#include "Connection/connect.h"

#define CLIENT_DB "Client"
#define SERVER_DB "Server"

namespace SQLDAL {
	class Statement {
	public:
		Statement(std::shared_ptr<Connect> connection);
		Statement() = default;
		virtual ~Statement();

	protected:


		void SetQuery(QSqlDatabase database);
		void ExectuteQuery(QString query);
		void ErrorInfo();

		std::shared_ptr<Connect> connection_;
		QSqlQuery query_;
	};
}
#endif  // !STATEMENT_H
