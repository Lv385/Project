#ifndef CLIENTDAL_H
#define CLIENTDAL_H


#include "statement.h"
#include "connection.h"



class ClientDAL :public Statement {
public:
	ClientDAL(const QString& connection_name);
	ClientDAL();
		Connection* connection;
};

#endif // !CLIENTDAL_H
