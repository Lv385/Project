#include <QtCore/QCoreApplication>
#include "AsyncServer.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	AsyncServer async_server; // run server
	return a.exec();
}
