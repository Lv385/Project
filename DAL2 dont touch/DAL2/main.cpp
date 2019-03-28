#include <QtCore/QCoreApplication>
#include <iostream>
#include "sqldal.h"
using namespace SQLDAL;

int main(int argc, char *argv[]) {

  QCoreApplication a(argc, argv);

  UnitOfWork db;
  db.GenerateUniqueConnection();

  auto user = db.GetEntity<SQLDAL::Friend>();
  QVector<Friends> fr = user->GetFriends();
  Friends frien;
  frien.id = 1111;
  frien.login = "fadasd";
  frien.name = "asd";
  frien.surname = "da";
  user->AddNewFriend(frien);
  /*QVector<Messages> vec = user->GetMessages();
  user->DeleteMessage();*/

  //fr_rq->Add(2, 3);
  //user->requests[0].Delete();
  return a.exec();
}
