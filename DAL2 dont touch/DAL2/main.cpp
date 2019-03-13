#include <QtCore/QCoreApplication>
#include "connection.h"
#include "statement.h"
#include "user.h"
#include<iostream>



int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  
  User u("marko");
  u.id = 7;
 // u.ip = "123.123.12.12";
  u.login = "marko";
  //u.password = "marko";
  //u.port = 1111;

  u.GetUser();
  

  std::cout << u.ip.toStdString();

  return a.exec();
}
