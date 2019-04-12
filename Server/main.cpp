#include <QtCore/QCoreApplication>
#include "async_server.h"
#include <iostream>
//#include <windows.h>
 // ALL COMMENTS Below IS FOR HIDING CONSOLE WINDOW THAT FOR FUTURe SO DONT Touch
int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
	AsyncServer async_server; // run server
  //HWND hWnd = GetConsoleWindow();
  //ShowWindow(hWnd, SW_HIDE);

 return a.exec();
}
