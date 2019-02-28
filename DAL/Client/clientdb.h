#ifndef CLIENTDB_H
#define CLIENTDB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QObject>
#include <QPair>
#include <iostream>
#include <QDateTime>
#include <vector>
#include <QtSql/qsqlresult.h>


struct Message
{
    int message_id;
    int owner_id;
    QString data;
    QDate date;
    QTime time;
    bool status;
};

struct User{
    int user_id;
    //QString user_login;
    QString user_name;
    QString user_surname;
    //QImage user_profile_photo;
};


class ClientDB
{
public:

    ClientDB();
   // ~ClientDB();

    void                 AddNewFriend(const QString& user_login, const int user_id);
    QPair<QString, int>  GetIPPort(const QString& user_login);
    void                 UpdateIPPort(const QString& user_login,const QString& new_user_ip, const int& new_user_port);
    void                 AddMessage(const Message&  message, const QString& user_login);
    std::vector<Message> GetMessages(const QString& user_login);
    void                 UpdateUserProfile(const QString& user_login, const QString& user_name, const QString& user_surname);
    std::vector<User>    GetFriends();
    void                 DeleteFriend(const QString& user_login);
    void                 SetFriendStatus(const QString& user_login, bool status);
    void                 SetMessageStatusRead(const int& message_id);
    bool                 GetFriendStatus(const QString& user_login);



private:
    int           CountOfFriends();
    int           CountOfMessages(const QString& user_login);
    void          CreateUserProfile(const unsigned int user_id);
    void          DeleteUserProfile(const QString& user_login);
    void          ErrorInfo(void);
    unsigned int  GetIDByLogin(const QString& user_login);

    QSqlDatabase data_base_;
    QSqlQuery    query_;
};

#endif // CLIENTDB_H
