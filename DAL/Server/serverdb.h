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

    void                    AddNewUser(const QString& new_user_login, const QString& new_user_password);

    void                    UpdateIPPort(const QString& user_login,const QString& new_user_ip, const int& new_user_port);//by login 
	void                    UpdateIPPort(const unsigned int& user_id, const QString& new_user_ip, const int& new_user_port);//by id

    QPair<QString, int>     GetIPPort(const QString& user_login);
	QPair<QString, int>     GetIPPort(const unsigned int& user_id);
	
    bool                    CheckUser(const QString& user_login, const QString& user_password);	
	QString					GetPasswordById(const unsigned int& user_id); //??????????????????????????????
	//UpdatePassword(user_login, old_passwrd, new_password);
    void                    AddFriend(const QString& user_login, const QString& second_user_login);
	void                    AddFriend(const unsigned int& user_id, const unsigned int& second_user_id);

    unsigned int            GetIDByLogin(const QString& user_login);//If login don't exist return id = 0	
	QString				    GetLoginByID(const unsigned int& user_id);// String will be empty if user id dont exist
	
	QVector<unsigned int>   GetFriends(unsigned const int& user_id);
	bool                    IsFriend(const QString& first_user_login, const QString& second_user_login);
	bool                    IsFriend(const unsigned int& first_user_id, const unsigned int& second_user_id);

private:
    int           FindMaxID();//Find maximal id in the table, if something go wrong return -1

    void          ErrorInfo();
	bool	      IsLoginExist(const QString& user_login);// Check that user exist

    QSqlDatabase  data_base_;
    QSqlQuery     query_;
};

#endif // SEVERDB_H
