#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class Client
{
public:
    Client();

    QString getUserName() const;
    void setUserName(const QString &value);

    QString getUserIp() const;
    void setUserIp(const QString &value);

    QString getUserPort() const;
    void setUserPort(const QString &value);

    QString getUserPassword() const;
    void setUserPassword(const QString &value);

private:
    QString userName;
    QString userIp;
    QString userPort;
    QString userPassword;
};

#endif // CLIENT_H
