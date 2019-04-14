#include <QtCore/QCoreApplication>
#include <iostream>
#include <QDataStream>
#include "async_server.h"
#include "../Encryption/aes_cypher.h"
using namespace std;
// ALL COMMENTS Below IS FOR HIDING CONSOLE WINDOW THAT FOR FUTURe SO DONT Touch
//#include <windows.h>
int main(int argc, char *argv[]) {

  QCoreApplication a(argc, argv);
	AsyncServer async_server; // run server
  //HWND hWnd = GetConsoleWindow();
  //ShowWindow(hWnd, SW_HIDE);
  QString str = "string";
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << str;
 
  AESCypher cpp;
  cpp.Encrypt(result,result);


 return a.exec();
}
