#include <QtCore/QCoreApplication>
#include <iostream>
#include "sqldal.h"
using namespace SQLDAL;

int main(int argc, char *argv[]) {

  QCoreApplication a(argc, argv);

  UnitOfWork db;
  auto user = db.GetEntity<SQLDAL::User>();
  //fr_rq->Add(2, 3);
  user->id = 3;
  user->GetFriendsRequest();
  std::cout << user->requests[0].first_user_id;
  //user->requests[0].Delete();
  return a.exec();
}
