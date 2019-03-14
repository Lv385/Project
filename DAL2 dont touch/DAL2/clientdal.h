#include "statement.h"
#include "connection.h"


class ClientDAL :public Statement {
public:
	ClientDAL(const QString& connection_name);
	ClientDAL();
	Connection* connection;
};