#include "chatserver.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ChatServer server;
    return a.exec();
}
