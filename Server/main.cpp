#include <QtCore/QCoreApplication>
#include <iostream>
#include <QDataStream>
#include "async_server.h"
#include "../Parser&Structs/parser.h"
using namespace std;
// ALL COMMENTS Below IS FOR HIDING CONSOLE WINDOW THAT FOR FUTURe SO DONT Touch
//#include <windows.h>
int main(int argc, char *argv[]) {

  QCoreApplication a(argc, argv);
	AsyncServer async_server; // run server
  //HWND hWnd = GetConsoleWindow();
  //ShowWindow(hWnd, SW_HIDE);

 return a.exec();
}
