#include <QtCore/QCoreApplication>
#include <iostream>
#include <QDataStream>
#include "async_server.h"
#include "../Encryption/aes_cypher.h"
#include "../Parser&Structs/parser.h"
using namespace std;
// ALL COMMENTS Below IS FOR HIDING CONSOLE WINDOW THAT FOR FUTURe SO DONT Touch
//#include <windows.h>
int main(int argc, char *argv[]) {

  QCoreApplication a(argc, argv);
	AsyncServer async_server; // run server
  //HWND hWnd = GetConsoleWindow();
  //ShowWindow(hWnd, SW_HIDE);

  /*QString str = "hello_oleksa_libomyr_marko";
  AbstractCypher *cpp;
  cpp = new AESCypher();
  cpp->Encrypt(cpp->ConvertStringToByteArr(str),str);*/

  DeleteNotificationInfo data;
  data.id = 5;
  QByteArray  arr= Parser::DeleteNotificationInfo_ToByteArray(data);
  data = Parser::ParseAsDeleteNotificationInfo(arr);
  qDebug() << data.id;

 return a.exec();
}
