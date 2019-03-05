#include "login.h"
#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
	//QApplication::setStyle(QStyleFactory::create("gtk"));
    QApplication a(argc, argv);
	MainWindow w;
    w.show();
	
	
    return a.exec();
}
