#include <QtCore/QCoreApplication>
#include <iostream>
#include "sqldal.h"

int main(int argc, char *argv[]) {

  QCoreApplication a(argc, argv);

  UnitOfWork db{};

  auto user = db.GetEntity<User>();

  user->id = 4;
  user->login = "marko";
  user->GetUser();
  std::cout << user->login.toStdString();

  return a.exec();
}
