#include "serverdb.h"



void ServerDB::NewConnection(const QString connection_name)
{
	QSqlDatabase data_base_ = QSqlDatabase::addDatabase("QSQLITE", connection_name);
	data_base_.setDatabaseName("../DAL/Server/Server");
	
	if (!data_base_.open()) {
		qDebug() << data_base_.lastError().text();
	}
	else {
		qDebug() << "success";
	}

	query_ = new  QSqlQuery(data_base_);

	if (!query_->exec("SELECT * FROM users")) {
		ErrorInfo();
	}
	else {
		qDebug() << "success";
	}
}

void ServerDB::CloseConncetion(const QString connection_name)
{
	delete query_;
	QSqlDatabase::removeDatabase(connection_name);
}


int ServerDB::FindMaxID() {

    if (!query_->exec("select MAX(user_ID) from users")) {
        ErrorInfo();
        return -1;
    } else {
         int new_user_id = 0;
         while (query_->next()) {
              new_user_id = query_->record().value(0).toInt();
         }
         ++new_user_id;
         return new_user_id;
    }
}

void ServerDB::AddNewUser(const QString& new_user_login ,const QString& new_user_password) {
    query_->prepare("INSERT INTO users (user_login ,user_password) VALUES (:new_user_login, :new_user_password)");
    query_->bindValue(":new_user_login",new_user_login);
    query_->bindValue(":new_user_password",new_user_password);
    if (!query_->exec()) {
        ErrorInfo();
    }
}

void ServerDB::UpdateIPPort(const QString& user_login, const QString& new_user_ip, const int& new_user_port) {
    query_->prepare("UPDATE users SET user_IP = :new_user_ip, user_port = :new_user_port WHERE user_login  = :user_login ");
    query_->bindValue(":user_login", user_login);
    query_->bindValue(":new_user_ip",new_user_ip);
    query_->bindValue(":new_user_port",new_user_port);
    if (!query_->exec()) {
        ErrorInfo();
    }
}

void ServerDB::UpdateIPPort(const unsigned int & user_id, const QString & new_user_ip, const int & new_user_port) {
	if (user_id < FindMaxID()) {
		query_->prepare("UPDATE users SET user_IP = :new_user_ip, user_port = :new_user_port WHERE user_ID  = :user_id ");
		query_->bindValue(":user_id", user_id);
		query_->bindValue(":new_user_ip", new_user_ip);
		query_->bindValue(":new_user_port", new_user_port);
		if (!query_->exec()) {
			ErrorInfo();
		}
	}
}

bool ServerDB::CheckUser(const QString& user_login, const QString& user_password) {
    query_->prepare("select user_password from users where user_login = :user_login");
    query_->bindValue(":user_login", user_login);
    QString result_of_query= "";

    if (query_->exec()) {
		while (query_->next()) {
			result_of_query = query_->record().value(0).toString();
		}
    } else {
        ErrorInfo();
    }

    if (user_password == result_of_query) {
        return  true;
    } else {
        return false;
    }
}

QString ServerDB::GetPasswordById(const unsigned int & user_id) {
	QString password = "";
	if (user_id <= FindMaxID()) {
		query_->prepare("select user_password from users where user_ID = :user_id");
		query_->bindValue(":user_id", user_id);

		if (query_->exec()) {
			while (query_->next()) {
				password = query_->record().value(0).toString();
			}
		}
		else {
			ErrorInfo();
		}
		return password;
	} else {
		qDebug() << "User id doesnt exist";
		return password;
	}
}

void ServerDB::ErrorInfo() {
    qDebug() << query_->lastError().databaseText();
    qDebug() << query_->lastError().driverText();
}

bool ServerDB::IsLoginExist(const QString& user_login) {
	unsigned int id = 0;
	query_->prepare("select user_ID from users where user_login = :user_login");
	query_->bindValue(":user_login", user_login);
	if (query_->exec()) {
		while (query_->next()) {
			id = query_->record().value(0).toUInt();
		}
	} else {
		ErrorInfo();
	}
	return 0 == id ? false : true;
}

QPair<QString, int> ServerDB::GetIPPort(const QString& user_login) {

	query_->prepare("select user_IP,user_port from users where user_login = :user_login");
	query_->bindValue(":user_login", user_login);
	QPair<QString, int> result_query;
	
	if (query_->exec()) {
		while (query_->next()) {
			result_query.first = query_->record().value(0).toString();
			result_query.second = query_->record().value(1).toInt();
		}
	} else {
		ErrorInfo();
	}
	return result_query;
    
}

QPair<QString, int> ServerDB::GetIPPort(const unsigned int & user_id) {
	query_->prepare("select user_IP,user_port from users where user_ID = :user_id");
	query_->bindValue(":user_id", user_id);
	QPair<QString, int> result_query;

	if (query_->exec()) {
		while (query_->next()) {
			result_query.first = query_->record().value(0).toString();
			result_query.second = query_->record().value(1).toInt();
		}
	} else {
		ErrorInfo();
	}
	return result_query;
}

bool ServerDB::IsFriend(const QString& first_user_login, const QString& second_user_login) {
    unsigned int id_of_first_user = GetIDByLogin(first_user_login);
    unsigned int id_of_second_user = GetIDByLogin(second_user_login);
    query_->prepare("SELECT COUNT(*)  FROM friends WHERE (second_user_ID = :id_of_second_user AND first_user_ID = :id_of_first_user) OR (first_user_ID = :id_of_second_user AND second_user_ID = :id_of_first_user)");
    query_->bindValue(":id_of_first_user",id_of_first_user);
    query_->bindValue(":id_of_second_user",id_of_second_user);
    int result = 0;
    if (query_->exec()) {
        while (query_->next()) {
              result = query_->record().value(0).toInt();
        }

        if (result == 2) {
            return true;
        } else {
            return false;
        }
    } else {
       ErrorInfo();
       return false;
    }

}

bool ServerDB::IsFriend(const unsigned int & first_user_id, const unsigned int & second_user_id) {
	query_->prepare("SELECT COUNT(*)  FROM friends WHERE (second_user_ID = :id_of_second_user AND first_user_ID = :id_of_first_user) OR (first_user_ID = :id_of_second_user AND second_user_ID = :id_of_first_user)");
	query_->bindValue(":id_of_first_user", first_user_id);
	query_->bindValue(":id_of_second_user", second_user_id);
	int result = 0;
	if (query_->exec()) {
		while (query_->next()) {
			result = query_->record().value(0).toInt();
		}

		if (result == 2) {
			return true;
		} else {
			return false;
		}
	} else {
		ErrorInfo();
		return false;
	}
}

unsigned int  ServerDB::GetIDByLogin(const QString& user_login) {
	if (IsLoginExist(user_login) == true) {
		query_->prepare("select user_ID from users where user_login = :user_login");
		query_->bindValue(":user_login", user_login);

		unsigned int id = 0;
		if (query_->exec()) {
			while (query_->next()) {
				id = query_->record().value(0).toUInt();
			}
		} else {
			ErrorInfo();
		}
		return id;
	} else {		
		return 0;
	}
}

QString ServerDB::GetLoginByID(const unsigned int & user_id) {
	QString login = "";
	if (user_id <= FindMaxID())
	{
		query_->prepare("select user_login from users where user_ID = :user_id");
		query_->bindValue(":user_id", user_id);

		if (query_->exec()) {
			while (query_->next()) {
				login = query_->record().value(0).toString();
			}
		}
		else {
			ErrorInfo();
		}
		return login;
	} else {
		qDebug() << "User id doesnt exist";
		return login;
	}
}

QVector<unsigned int> ServerDB::GetFriends(unsigned const int & user_id) {
	query_->prepare("SELECT second_user_id FROM friends WHERE first_user_id = :user_id");
	query_->bindValue(":user_id", user_id);
	QVector<unsigned int> id_result;

	if (query_->exec()) {
		while (query_->next()) {
             id_result.push_back(query_->record().value(0).toUInt());
		}
	} else {
		ErrorInfo();
	}

	unsigned int counter = 0;
	while (counter < id_result.size()) {
		if (false == IsFriend(user_id, id_result[counter++])) {
			id_result.remove(counter - 1);
		}
	}
	return id_result;
}

void ServerDB::addPendingFriendRequest(const unsigned int& user_id, const unsigned int& pending_user) {
  
    query_->prepare(
        "INSERT INTO pending_friend_request (user, pending_users) VALUES (:f_id, "
        ":s_id)");
    query_->bindValue(":f_id", user_id);
    query_->bindValue(":s_id", pending_user);
    if (!query_->exec()) {
      ErrorInfo();
    }
  
}

QVector<unsigned int> ServerDB::GetPendingFriendRequests(unsigned const int& user_id) {
  query_->prepare(
      "SELECT pending_users FROM pending_friend_request WHERE user = :user_id");
  query_->bindValue(":user_id", user_id);
  QVector<unsigned int> id_result;

  if (query_->exec()) {
    while (query_->next()) {
      id_result.push_back(query_->record().value(0).toUInt());
    }
  } else {
    ErrorInfo();
  }

  return id_result;
}

void ServerDB::addPendingNotification(const unsigned int& user_id,
                                      const unsigned int& pending_user) {
  query_->prepare(
      "INSERT INTO pending_friend_notification (user_dst, user_src) VALUES (:f_id, "
      ":s_id)");
  query_->bindValue(":f_id", user_id);
  query_->bindValue(":s_id", pending_user);
  if (!query_->exec()) {
    ErrorInfo();
  }
}

QVector<unsigned int> ServerDB::GetPendingNotification(
    unsigned const int& user_id) {
  query_->prepare(
      "SELECT user_src FROM pending_friend_notification WHERE user_dst = :user_id");
  query_->bindValue(":user_id", user_id);
  QVector<unsigned int> id_result;

  if (query_->exec()) {
    while (query_->next()) {
      id_result.push_back(query_->record().value(0).toUInt());
    }
  } else {
    ErrorInfo();
  }

  return id_result;
}

void ServerDB::AddFriend(const QString& user_login ,const QString& second_user_login) {
     if (!IsFriend(user_login,second_user_login)) {
         unsigned int f_id = GetIDByLogin(user_login);
         unsigned int s_id = GetIDByLogin(second_user_login);
         query_->prepare("INSERT INTO friends (first_user_ID,second_user_ID) VALUES (:f_id, :s_id)");
         query_->bindValue(":f_id",f_id);
         query_->bindValue(":s_id",s_id);
         if (!query_->exec()) {
            ErrorInfo();
         }
     } else {
          qDebug("You are already friends");
     }
}

void ServerDB::AddFriend(const unsigned int & user_id, const unsigned int & second_user_id) {
	if (!IsFriend(user_id, second_user_id)) {
		query_->prepare("INSERT INTO friends (first_user_ID,second_user_ID) VALUES (:f_id, :s_id)");
		query_->bindValue(":f_id", user_id);
		query_->bindValue(":s_id", second_user_id);
		if (!query_->exec()) {
			ErrorInfo();
		}
	} else {
		qDebug("You are already friends");
	}
}

void ServerDB::DeleteAllFriends(const unsigned int& user) {
  query_->prepare(
      "DELETE FROM friends WHERE first_user_ID = :user_to_delete");
  query_->bindValue(":user_to_delete", user);
  if (!query_->exec()) {
    ErrorInfo();
  }

}

void ServerDB::DeleteAllPendingRequest(const unsigned int& user_id) {
  query_->prepare(
      "DELETE FROM pending_friend_request WHERE user = :user_to_delete");
  query_->bindValue(":user_to_delete", user_id);  
  if (!query_->exec()) {
    ErrorInfo();
  }
}

void ServerDB::DeleteAllPendingNotifications(const unsigned int& user_id) {
  query_->prepare(
      "DELETE FROM pending_friend_notification WHERE user_dst = :user_to_delete");
  query_->bindValue(":user_to_delete", user_id);
  if (!query_->exec()) {
    ErrorInfo();
  }
}


