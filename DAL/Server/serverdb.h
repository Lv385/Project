#ifndef SEVERDB_H
#define SEVERDB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QSqlRecord>
#include <QSqlResult>
#include <QDebug>
#include <QObject>
#include <QPair>
#include <iostream>

//Class uses to make connection server-data base
//It consist all methods needed to work with db
class ServerDB
{
public:
            ServerDB();
    virtual~ServerDB();

    void                 AddNewUser(const QString& new_user_login ,const QString& new_user_password);
    void                 UpdateIPPort(const QString& user_login,const QString& new_user_ip, const int& new_user_port);
    QPair<QString, int>  GetIPPort(const QString& user_login, const QString& second_user_login);
    bool                 CheckUser(const QString& user_login ,const QString& user_password);
    void                 AddFriend(const QString& user_login ,const QString& second_user_login);
    unsigned int         GetIDByLogin(const QString& user_login);//if login dont exist return id = 0

private:
    int           FindMaxID(void);//Find maximal id in the table, if something go wrong return -1
    bool          IsFriend(const QString& first_user_login, const QString& second_user_login);
    void          ErrorInfo(void);

    QSqlDatabase  data_base_;
    QSqlQuery     query_;
};

#endif // SEVERDB_H
