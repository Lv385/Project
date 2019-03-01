#include "serverdb.h"

ServerDB::ServerDB()
{
    data_base_=QSqlDatabase::addDatabase("QSQLITE");
    data_base_.setDatabaseName("../DAL/Server/Server");
    //data_base_.setDatabaseName("server");
    if (!data_base_.open())
    {
        qDebug()<<data_base_.lastError().text();
    }
    else
    {
        qDebug() << "success";
    }

    query_ = QSqlQuery(data_base_);

	if (!query_.exec("SELECT * FROM users"))
	{
		ErrorInfo();
	}
	else
	{
		qDebug() << "success";
	}
}

ServerDB::~ServerDB()
{
    data_base_.close();
}


int ServerDB::FindMaxID()
{

    if (!query_.exec("select MAX(user_ID) from users"))//TODO: exception if bad
    {
        ErrorInfo();
        return -1;
    }
    else
    {
         int new_user_id = 0;
         while (query_.next())
         {
              new_user_id = query_.record().value(0).toInt();
         }
         ++new_user_id;
         return new_user_id;
    }
}

void ServerDB::AddNewUser(const QString& new_user_login ,const QString& new_user_password)
{
    query_.prepare("INSERT INTO users (user_login ,user_password) VALUES (:new_user_login, :new_user_password)");
    query_.bindValue(":new_user_login",new_user_login);
    query_.bindValue(":new_user_password",new_user_password);
    if (!query_.exec())//TODO: exception if bad????
    {
        ErrorInfo();
    }
}

void ServerDB::UpdateIPPort(const QString& user_login,const QString& new_user_ip, const int& new_user_port)
{
    query_.prepare("UPDATE users SET user_IP = :new_user_ip, user_port = :new_user_port WHERE user_login  = :user_login ");
    query_.bindValue(":user_login", user_login);
    query_.bindValue(":new_user_ip",new_user_ip);
    query_.bindValue(":new_user_port",new_user_port);
    if (!query_.exec())//TODO: exception if bad
    {
        ErrorInfo();
    }
}

bool ServerDB::CheckUser(const QString& user_login ,const QString& user_password)
{
    query_.prepare("select user_password from users where user_login = :user_login");
    query_.bindValue(":user_login", user_login);
    QString result_of_query= "";

    if (query_.exec())
    {
        while (query_.next())
        {
            result_of_query = query_.record().value(0).toString();
        }
    }
    else
    {
        ErrorInfo();
    }

    if (user_password == result_of_query)
    {
        return  true;
    }
    else
    {
        return false;
    }
}

void ServerDB::ErrorInfo()
{
    qDebug() << query_.lastError().databaseText();
    qDebug() << query_.lastError().driverText();
}

QPair<QString, int> ServerDB::GetIPPort(const QString& user_login, const QString& second_user_login="admin")//TODO: Check is friend????
{
    if (true == IsFriend(user_login,second_user_login))
    {
        query_.prepare("select user_IP,user_port from users where user_login = :user_login");
        query_.bindValue(":user_login", user_login);
        QPair<QString, int> result_query;
        if(IsFriend("admin",user_login))
        if (query_.exec())
        {
            while (query_.next())
            {
                 result_query.first = query_.record().value(0).toString();
                 result_query.second = query_.record().value(1).toInt();
            }
        }
        else
        {
           ErrorInfo();
        }
        return result_query;
    }
    else
    {
        qDebug() << "You can't take info about this user";
    }
}

bool ServerDB::IsFriend(const QString& first_user_login, const QString& second_user_login)
{
    unsigned int id_of_first_user = GetIDByLogin(first_user_login);
    unsigned int id_of_second_user = GetIDByLogin(second_user_login);
    query_.prepare("SELECT COUNT(*)  FROM friends WHERE (second_user_ID = :id_of_second_user AND first_user_ID = :id_of_first_user) OR (first_user_ID = :id_of_second_user AND second_user_ID = :id_of_first_user)");
    query_.bindValue(":id_of_first_user",id_of_first_user);
    query_.bindValue(":id_of_second_user",id_of_second_user);
    int result = 0;
    if (query_.exec())
    {
        while (query_.next())
        {
              result = query_.record().value(0).toInt();
        }

        if (result == 2)
        {
            std::cout << true;
            return true;
        }
        else
        {
            std::cout << false;
            return false;
        }
    }
    else
    {
       ErrorInfo();
       return false;
    }

}

unsigned int  ServerDB::GetIDByLogin(const QString& user_login)//TODO if user login doesnt exist
{

     query_.prepare("select user_ID from users where user_login = :user_login");
     query_.bindValue(":user_login", user_login);

     unsigned int id = 0;
     if (query_.exec())
     {
         while (query_.next())
         {
              id = query_.record().value(0).toUInt();
         }
     }
     else
     {
        ErrorInfo();
     }
     return id;

}

void ServerDB::AddFriend(const QString& user_login ,const QString& second_user_login)
{
     if (!IsFriend(user_login,second_user_login))
     {
         unsigned int f_id = GetIDByLogin(user_login);
         unsigned int s_id = GetIDByLogin(second_user_login);
         query_.prepare("INSERT INTO friends (first_user_ID,second_user_ID) VALUES (:f_id, :s_id)");
         query_.bindValue(":f_id",f_id);
         query_.bindValue(":s_id",s_id);
         if (!query_.exec())
         {
            ErrorInfo();
         }
     }
     else
     {
          qDebug("You are already friends");
     }
}


