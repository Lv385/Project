#include "clientdb.h"


ClientDAL::ClientDB::ClientDB() {
    data_base_=QSqlDatabase::addDatabase("QSQLITE");
    data_base_.setDatabaseName("../DAL/Client/Client");

    if (!data_base_.open()) {
        qDebug()<<data_base_.lastError().text();
    } else {
        qDebug() << "success";
    }

    query_ = QSqlQuery(data_base_);

    if (!query_.exec("select * from friends")) {
        ErrorInfo();
    } else {
        qDebug()<<"success";
    }
}

ClientDAL::ClientDB::~ClientDB() {
	data_base_.close();
	data_base_.removeDatabase("../DAL/Client/Client");
	query_.finish();
}

void ClientDAL::ClientDB::AddNewFriend(const QString &user_login, const int user_id) {
    query_.prepare("INSERT INTO friends (user_id, user_login) VALUES (:new_user_id, :new_user_login)");
        query_.bindValue(":new_user_id",user_id);
        query_.bindValue(":new_user_login",user_login);
        if (!query_.exec()) {
            ErrorInfo();
        }
    CreateUserProfile(user_id);
}

QPair<QString, int> ClientDAL::ClientDB::GetIPPort(const QString &user_login) {
    query_.prepare("select user_IP,user_port from friends where user_login = :user_login");
    query_.bindValue(":user_login", user_login);

    QPair<QString, int> result_query;

	if (query_.exec()) {
		while (query_.next()) {
			result_query.first = query_.record().value(0).toString();
			result_query.second = query_.record().value(1).toInt();
		}
	} else {
       ErrorInfo();
    }
    return result_query;
}

QPair<QString, int> ClientDAL::ClientDB::GetIPPort(const int &user_id) {
	return GetIPPort(GetLoginById(user_id));
}

void ClientDAL::ClientDB::UpdateIPPort(const QString &user_login, const QString &new_user_ip, const int &new_user_port) {
    query_.prepare("UPDATE friends SET user_IP = :new_user_ip, user_port = :new_user_port WHERE user_login  = :user_login ");
    query_.bindValue(":user_login", user_login);
    query_.bindValue(":new_user_ip",new_user_ip);
    query_.bindValue(":new_user_port",new_user_port);

    if (!query_.exec()) {
       ErrorInfo();
    }
}

void ClientDAL::ClientDB::UpdateIPPort(const int &user_id, const QString &new_user_ip, const int &new_user_port) {

	UpdateIPPort(GetLoginById(user_id), new_user_ip, new_user_port);
}

void ClientDAL::ClientDB::AddMessage(const Message &message, const QString& user_login) {

        int user_id = GetIDByLogin(user_login);
        query_.prepare("INSERT INTO Messages (user_ID, owner_ID, message_data,message_date,message_tima, message_status) VALUES ( :new_user_ID , :new_owner_ID, :new_message_data, :new_message_date,:new_message_time,:new_message_status)");
        query_.bindValue(":new_user_ID", user_id);
        query_.bindValue(":new_owner_ID", message.owner_id);
        query_.bindValue(":new_message_data", message.data);
        query_.bindValue(":new_message_date", message.date.toString());
        query_.bindValue(":new_message_time", message.time.toString());
        query_.bindValue(":new_message_status", message.status);

        if (!query_.exec()) {
            ErrorInfo();
        }
}

void ClientDAL::ClientDB::AddMessage(const Message &message, const int& user_id) {
	AddMessage(message, GetLoginById(user_id));
}

QVector<ClientDAL::Message> ClientDAL::ClientDB::GetMessages(const QString &user_login) {
    int count_of_messages = CountOfMessages(user_login);

    unsigned int user_id = GetIDByLogin(user_login);
    QVector<Message> messages(count_of_messages);
    query_.prepare("SELECT owner_ID,message_data,message_date,message_tima, message_ID FROM Messages WHERE user_ID = :user_id ");
    query_.bindValue(":user_id", user_id );
    int counter = 0;
    if (query_.exec())
    {
        while (query_.next())
        {
             messages[counter].owner_id = query_.record().value(0).toInt();
             messages[counter].data = query_.record().value(1).toString();
             messages[counter].date = query_.record().value(2).toDate();
             messages[counter].time = query_.record().value(3).toTime();
             messages[counter++].message_id= query_.record().value(4).toInt();
        }
    }
    else
    {
       ErrorInfo();
    }

    return messages;
}

QVector<ClientDAL::Message> ClientDAL::ClientDB::GetMessages(const int &user_id) {
	return GetMessages(GetLoginById(user_id));
}

void ClientDAL::ClientDB::UpdateUserProfile(const QString &user_login, const QString &user_name, const QString &user_surname) {
    int user_id = GetIDByLogin(user_login);
    query_.prepare("UPDATE friend_info SET user_name = :new_user_name, user_surname = :new_user_surname WHERE user_ID  = :user_id ");
    query_.bindValue(":user_id", user_id);
    query_.bindValue(":new_user_name",user_name);
    query_.bindValue(":new_user_surname",user_surname);
    if (!query_.exec()) {
       ErrorInfo();
    }
}

void ClientDAL::ClientDB::UpdateUserProfile(const int &user_id, const QString &user_name, const QString &user_surname) {
	UpdateUserProfile(GetLoginById(user_id), user_name, user_surname);
}

QVector<ClientDAL::User> ClientDAL::ClientDB::GetFriends() {
    unsigned int count_of_friends = CountOfFriends();


    QVector<User>friends(count_of_friends);
    query_.prepare("SELECT user_ID, user_name, user_surname FROM friend_info");

    int counter = 0;
    if (query_.exec()) {
        while (query_.next()) {
             friends[counter].user_id = query_.record().value(0).toInt();
             friends[counter].user_name = query_.record().value(1).toString();
             friends[counter++].user_surname = query_.record().value(2).toString();
        }
    } else {
       ErrorInfo();
    }

    return friends;
}

QVector<QString> ClientDAL::ClientDB::GetFriendsLogin() {
	unsigned int count_of_friends = CountOfFriends();

	QVector<QString>friends(count_of_friends);
	query_.prepare("SELECT user_login FROM friends");

	int counter = 0;
	if (query_.exec()) {
		while (query_.next()) {
			friends[counter++] = query_.record().value(0).toString();
		}
	} else {
		ErrorInfo();
	} 
	return friends;
}



void ClientDAL::ClientDB::DeleteFriend(const QString &user_login) {
    DeleteUserProfile(user_login);

    query_.prepare("DELETE FROM friends WHERE user_login  = :user_login ");
    query_.bindValue(":user_login", user_login);

    if (!query_.exec()) {
       ErrorInfo();
    }

}

void ClientDAL::ClientDB::DeleteFriend(const int &user_id) {
	DeleteFriend(GetLoginById(user_id));
}

void ClientDAL::ClientDB::SetFriendStatus(const QString &user_login, bool status) {
    int user_id = GetIDByLogin(user_login);
    query_.prepare("UPDATE friends SET user_status = :new_user_status WHERE user_ID  = :user_id ");
    query_.bindValue(":user_id", user_id);
    query_.bindValue(":new_user_status", status);
    if (!query_.exec()) {
       ErrorInfo();
    }
}

void ClientDAL::ClientDB::SetFriendStatus(const int &user_id, bool status) {
	SetFriendStatus(GetLoginById(user_id), status);
}

void ClientDAL::ClientDB::SetMessageStatusRead(const int &message_id) {
    query_.prepare("UPDATE Messages SET message_status = true WHERE message_ID  = :message_id");
    query_.bindValue(":message_id", message_id);
    if (!query_.exec()) {
       ErrorInfo();
    }
}

bool ClientDAL::ClientDB::GetFriendStatus(const QString &user_login) {
    query_.prepare("SELECT user_status FROM friends WHERE user_login  = :user_login ");
        query_.bindValue(":user_login",user_login);
        bool status = false;
        if (query_.exec()) {
            while (query_.next()) {
                 status = query_.record().value(0).toBool();
            }
        } else {
           ErrorInfo();
        }
        return status;
}

bool ClientDAL::ClientDB::GetFriendStatus(const int &user_id) {
	return GetFriendStatus(GetLoginById(user_id));
}

int ClientDAL::ClientDB::CountOfFriends()
{
    int count_of_friends = 0;
    query_.prepare("SELECT COUNT(user_ID) FROM friends");
    if (query_.exec()) {
        while (query_.next()) {
             count_of_friends = query_.record().value(0).toInt();
        }
    } else {
       ErrorInfo();
    }
    return count_of_friends;
}

int ClientDAL::ClientDB::CountOfMessages(const QString &user_login) {
    unsigned int count_of_messages = 0;
    unsigned int user_id = GetIDByLogin(user_login);
    query_.prepare("SELECT COUNT(user_ID) FROM Messages WHERE user_ID = :user_id ");
    query_.bindValue(":user_id", user_id );
    if (query_.exec()) {
        while (query_.next()) {
             count_of_messages = query_.record().value(0).toUInt();
        }
    } else {
       ErrorInfo();
    }
    return count_of_messages;
}



void ClientDAL::ClientDB::CreateUserProfile(const unsigned int user_id) {
    query_.prepare("INSERT INTO friend_info (user_ID) VALUES ( :new_user_ID)");
    query_.bindValue(":new_user_ID", user_id);
    //query_.bindValue(":new_user_name", user_name);
    //query_.bindValue(":new_user_surname", user_surname);

    if (!query_.exec()) {
        ErrorInfo();
    }
}

void ClientDAL::ClientDB::DeleteUserProfile(const QString &user_login) {
    uint user_id = GetIDByLogin(user_login);

    query_.prepare("DELETE FROM friend_info WHERE user_ID  = :user_id ");
    query_.bindValue(":user_id", user_id);

    if (!query_.exec()) {
       ErrorInfo();
    }


}


void ClientDAL::ClientDB::ErrorInfo() {
    qDebug() << query_.lastError().databaseText();
    qDebug() << query_.lastError().driverText();
}

unsigned int ClientDAL::ClientDB::GetIDByLogin(const QString &user_login) {
	query_.prepare("select user_id from friends where user_login = :user_login");
	query_.bindValue(":user_login", user_login);

	unsigned int id = 0;
	if (query_.exec()) {
		while (query_.next()) {
			id = query_.record().value(0).toInt();
		}
	} else {
		ErrorInfo();
	}
	return id;
}

unsigned ClientDAL::ClientDB::GetIDByIpPort(const QString & ip, int port) {
	query_.prepare("select user_id from friends where user_IP = :ip and user_port = :port");
	query_.bindValue(":ip", ip);
	query_.bindValue(":port", port);

	unsigned int id = 0;
	if (query_.exec()) {
		while (query_.next()) {
			id = query_.record().value(0).toInt();
		}
	} else {
		ErrorInfo();
	}
	return id;
}


QString ClientDAL::ClientDB::GetLoginById(const int &user_id) {
	query_.prepare("select user_login from friends where user_id = :user_id");
	query_.bindValue(":user_id", user_id);

	QString login = "";
	if (query_.exec()) {
		while (query_.next()) {
			login = query_.record().value(0).toString();
		}
	} else {
		ErrorInfo();
	}
	return login;
}
