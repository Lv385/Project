#include <QtCore/QCoreApplication>
#include "connection.h"
#include "statement.h"
#include "user.h"
#include "message.h"
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
  Message m("marko");
  m.chat_id = 1;
  QVector<Message> result = m.GetMessages();
  

  std::cout << result[0].data.toStdString();

  return a.exec();
}
