#include <QtCore/QCoreApplication>
#include <iostream>
#include "AsyncServer.h"


int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  /*
  UnitOfWork db{};
  auto user = db.GetEntity<User>();
  user->id = 4;
  user->GetUser();
  user->ip = "123.123.123.123";
  user->UpdateUser();
  QVector<int> f = user->GetFriendsRequest();
  std::cout << user->login.toStdString();
  */

  AsyncServer async_server; // run server
  return a.exec();
}
