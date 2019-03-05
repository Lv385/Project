
#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
	//QApplication::setStyle(QStyleFactory::create("gtk"));
    QApplication a(argc, argv);
	MainWindow w;
    w.show();
	
	
    return a.exec();
}
