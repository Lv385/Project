#include "clientdal.h"

ClientDAL::ClientDAL(const QString & connection_name) : Statement()
{
	connection = new Connection(connection_name);
	connection->Open("Client");//TODO: Correct path
	SetQuery(connection->GetDB());
}

ClientDAL::ClientDAL()
{
}
