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

  //UnitOfWork object{};

  //auto f = object.GetEntity<User>();
  //f->id = 1;
  //f->AddNewFriend(2);


  

  UnitOfWork obj{};

  UnitOfWork obvj2{};
  
 

  auto user = obj.GetEntity<User>();
  //user->id = 5;
 // user->login = "Sviatoslav";
  //user->password = "password";
  //user->ip = "444.444.4.4";
  //user->port = 1111;
  //user->AddNewUser();											//видалення з friend and friend_request

  //user->GetUser();



  //user->GetUser();

  //user->port = 9000;
  //user->UpdateUser();

  //QVector <int>f = user->GetFriendsRequest();
  //std::cout << f[0];


//  QVector <int> ff = user->get
  //user->login = "marko";
  //user->GetUser();

  //user->AddNewFriend(2);

  //std::cout << user->id;











  //QVector<int> f1 = f->GetFriends();
  //f->id = 2;
  //QVector<int> f2 = f->GetFriendsRequest();









  

  //auto user = object.GetEntity<User>();
  //user->id = 1;
  //user->DeleteUser();
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
