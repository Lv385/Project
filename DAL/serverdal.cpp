#include "serverdal.h"

ServerDAL::ServerDAL(const QString& connection_name)
    : Statement() {
  connection = new Connection(connection_name);
  connection->Open("Server");//TODO: Correct path
  SetQuery(connection->GetDB());
}
