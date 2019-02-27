#include "client.h"

Client::Client()
{

}

QString Client::getUserName() const
{
    return userName;
}

void Client::setUserName(const QString &value)
{
    userName = value;
}

QString Client::getUserIp() const
{
    return userIp;
}

void Client::setUserIp(const QString &value)
{
    userIp = value;
}

QString Client::getUserPort() const
{
    return userPort;
}

void Client::setUserPort(const QString &value)
{
    userPort = value;
}

QString Client::getUserPassword() const
{
    return userPassword;
}

void Client::setUserPassword(const QString &value)
{
    userPassword = value;
}
