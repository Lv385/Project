#include <QtCore/QCoreApplication>
#include <iostream>
#include "connection.h"
#include "friend.h"
#include "message.h"
#include "statement.h"
#include "unitofwork.h"
#include "user.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  UnitOfWork object{};


  auto user = object.GetEntity<User>();
  user->id = 1;
  user->DeleteUser();
 // std::cout
  //auto mes = object.GetEntity<Message>();
  //mes->id = 78;
  //mes->chat_id = 1;
  //mes->data = "loxqewqewqewqewqewqqw";
  //mes->UpdateMessage();
  //mes->owner_id = 2;
  //mes->date = QDate::currentDate();
  //mes->time = QTime::currentTime();
  //QVector <Message> m = mes->GetMessages();
  //std::cout << m[0].data.toStdString();


  //auto friends = object.GetEntity<Friend>();
  //friends->id = 4;
  //friends->login = "Yulik";
  //friends->port = 9999;
  //friends->ip = "123.123.123.1";
  //friends->name = "Mddaewy";
  //friends->surname = "Mdasdasy";
  //friends->status = false;
  //std::cout << friends->UpdateQuery().toStdString();
  //friends->AddNewFriend();
  //friends->UpdateFriend();
  //QVector<Friend> f = friends->GetFriends();
  //std::cout << f[0].login.toStdString();
  return a.exec();
}
