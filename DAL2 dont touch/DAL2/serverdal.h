#ifndef SERVERDAL_H
#define SERVEDAL_H

#include "connection.h"
#include "statement.h"

class ServerDAL : public Statement {
 public:
  ServerDAL(const QString& connection_name);
  Connection* connection;
};

#endif  // SERVERDAL_H