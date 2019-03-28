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
  frien.login = "fa";
  frien.name = "asd";
  frien.surname = "da";
  user->AddNewFriend(frien);
  /*QVector<Messages> vec = user->GetMessages();
  user->DeleteMessage();*/

  //fr_rq->Add(2, 3);
  user->id = 3;
  user->GetFriendsRequest();
  std::cout << user->requests[0].first_user_id;
  //user->requests[0].Delete();
  return a.exec();
}
