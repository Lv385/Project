#include <QtCore/QCoreApplication>
#include "connection.h"
#include "statement.h"
#include "user.h"
#include "message.h"
#include "friend.h"
#include<iostream>



int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  
  //User u("marko");
  //u.id = 7;
 // u.ip = "123.123.12.12";
  //u.login = "marko";
  //u.password = "marko";
  //u.port = 1111;

  //u.GetUser();
 // Message m("marko");
  //m.chat_id = 1;
  //m.owner_id = 1;
  //m.data = "marko";
  //m.date = QDate::currentDate();
  //m.time = QTime::currentTime();
  //m.status = false;
  //m.AddNewMessage();
  //QVector<Message> result = m.GetMessages();
  Friend f("marko");
  QVector<Friend> ff = f.GetFriends();
  for (auto i : ff) {
	  std::cout << i.id<<" ";
	  std::cout << i.name.toStdString() << " ";
	  std::cout << i.surname.toStdString() << " ";
	  std::cout << i.ip.toStdString() << " ";
	  std::cout << i.port << " ";
	  std::cout << i.login.toStdString() << " ";
	  std::cout << i.status << std::endl;

  }
  
 // std::cout << result[0].data.toStdString();

  return a.exec();
}
