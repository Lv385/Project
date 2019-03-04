#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Login w;
	MainWindow w;
    w.show();

    return a.exec();
}
