#include <QtCore/QCoreApplication>
#include "WebToken.h"
#include <iostream>
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	WebToken wt;
        wt.SetHeader("SPEK");
        wt.SetPayload(1);
        wt.GenerateToken("key");
        std::cout << wt.token_.toStdString();
	return a.exec();
}
