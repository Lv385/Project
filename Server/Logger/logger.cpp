#pragma once
#include "logger.h" 

// void Logger::WriteLogToFile(QString& filename, QString& text)
void Logger::WriteLogToFile(QString& text) {
  //QFile file(filename);
  QFile file("LOG.txt");
  if (file.open(QIODevice::Append | QIODevice::Text)) {
    QTextStream stream(&file);
    stream << text << endl;
    file.close();
  }
}

QString Logger::ConvertQuint8ToString(quint8 num) {
  QString tmp;
  return tmp.setNum(num);
}
QString Logger::ConvertQuint16ToString(quint16 num) {
  QString tmp;
  return tmp.setNum(num);
}
QString Logger::ConvertQuint32ToString(quint32 num) {
  QString tmp;
  return tmp.setNum(num);
}

void Logger::LogOut(QString &IpAndPort, QByteArray raw_data) {
  RemoveShit(IpAndPort);
  if (ifLogingEnable) {
    QString outingString;  
    QString time = QDateTime::currentDateTime().toString("dd.MM hh:mm:ss ");
    quint8 type = Parser::getRequestType(raw_data);
    QString str_t = ConvertQuint8ToString(type);
    QString for_empty = "("+ str_t + ")" + "+empty{}\n";
    QString for_struct;
    switch (type) {
    // DONE
    case (quint8)ServerRequests::LOGIN_SUCCEED: {
      outingString = time+IpAndPort + " out: " + "LOGIN_SUCCEED"+ for_empty;
      qDebug().noquote() << outingString;
      WriteLogToFile(outingString);
      break;
    }
    //DONE                                            
    case (quint8)ServerRequests::LOGIN_FAILED: {
      outingString = time+IpAndPort + " out: LOGIN_FAILED"+ for_empty;
      qDebug().noquote() << outingString;
      WriteLogToFile(outingString);
      break;
    }
    //DONE                                           
    case (quint8)ServerRequests::REGISTER_FAILED: {
      outingString = time + IpAndPort + " out: REGISTER_FAILED" + for_empty;
      qDebug().noquote() << outingString;
      WriteLogToFile(outingString);
      break;
    }
    //DONE
    case (quint8)ServerRequests::FRIEND_REQUEST_FAILED: {
      outingString =time + IpAndPort + " out: FRIEND_REQUEST_FAILED" + for_empty;
      qDebug().noquote() << outingString;
      WriteLogToFile(outingString);
      break;
    }
    // DONE
    case (quint8)ServerRequests::FRIEND_REQUEST_SUCCEED: {
      outingString = time + IpAndPort + " out: FRIEND_REQUEST_SUCCEED(" + for_empty;
      qDebug().noquote() << outingString;
      WriteLogToFile(outingString);
      break;
    }
    //DONE                                                     
    case (quint8)ClientRequest::LOGIN: {
      LoginInfo out;
      out = Parser::ParseAsLoginInfo(raw_data);
      outingString =time+IpAndPort+ " in: LOGIN("+str_t+")" + Log_LoginInfo(out);
      qDebug().noquote() << outingString ;
      WriteLogToFile(outingString);
      break;
    }
    //DONE                              
    case (quint8)ClientRequest::REGISTER: {
      RegisterInfo out;
      out = Parser::ParseAsRegisterInfo(raw_data);
      outingString = time + IpAndPort + " in: REGISTER(" + str_t +
                     ")"+Log_RegisterInfo(out);
      qDebug().noquote() << outingString;
      WriteLogToFile(outingString);
      break;
    }
     //DONE                            
    case (quint8)ServerRequests::REGISTER_SUCCEED: {
      RegisterSuccessInfo out;
      out = Parser::ParseAsRegisterSuccessInfo(raw_data);
      outingString = time+IpAndPort+" out: REGISTER_SUCCEED(" +
        ConvertQuint8ToString(type) + ")" +
        Log_RegisterSuccessInfo(out);

      qDebug().noquote() << outingString;
      WriteLogToFile(outingString);
      break;
    }
    //DONE
    case (quint8)ClientRequest::FRIEND_REQUEST: {
      FriendRequestInfo out;
      out = Parser::ParseAsFriendRequestInfo(raw_data);
      outingString = time + IpAndPort +" in: FRIEND_REQUEST(" +
                     ConvertQuint8ToString(type) + ")" + Log_FriendRequestInfo(out);
      qDebug().noquote() << outingString;
      WriteLogToFile(outingString);
      break;
    }
    //DONE                                           
    case (quint8)ServerRequests::ADD_FRIEND_REQUEST: {
      AddFriendInfo out;
      out = Parser::ParseAsAddFriendInfo(raw_data);
      outingString = time + IpAndPort +" out: ADD_FRIEND_REQUEST(" +
        ConvertQuint8ToString(type) + ")" +
        Log_AddFriendInfo(out);
      qDebug().noquote() << outingString;
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::FRIEND_UPDATE_INFO: {
      FriendUpdateInfo out;
      out = Parser::ParseAsFriendUpdateInfo(raw_data);
      outingString = time + IpAndPort +"out: FRIEND_UPDATE_INFO(" +
        ConvertQuint8ToString(type) + ") " +
        Log_FriendUpdateInfo(out);
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::NEW_FRIEND_INFO: {
      NewFriendInfo out;
      out = Parser::ParseAsNewFriendInfo(raw_data);
      outingString = time+IpAndPort+"out:NEW_FRIEND_INFO (" +
        ConvertQuint8ToString(type) + ") " +
        Log_NewFriendInfo(out);
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    }
  }
}
//DONE
QString Logger::Log_RegisterSuccessInfo(RegisterSuccessInfo& out) {  
  return "\n\t\tRegisterSuccessInfo{ id:" + ConvertQuint32ToString(out.id) +
         " }\n" ;
}


//test // b2 upper intermediate
QString Logger::Log_FriendUpdateInfo(FriendUpdateInfo& out) {
  
  return "\n\t\tFriend_Update_Info{  ip: " + out.ip.toString() +
         "\n\t\tPort: " + ConvertQuint16ToString(out.port) +
         "\n\t\tID: " + ConvertQuint32ToString(out.id) + " }\n";
}
//DONE
QString Logger::Log_LoginInfo(LoginInfo& out) {  
  return "\n\t\tLoginInfo{port: " + ConvertQuint16ToString(out.port) +
         " \n\t\tid: " + ConvertQuint32ToString(out.id) +
         " \n\t\tpassword: " + out.password+"}\n";  
}
//DONE
QString Logger::Log_RegisterInfo(RegisterInfo& out) { 
  return "\n\t\tRegisterInfo{ port: " + ConvertQuint16ToString(out.port) +
         "\n\t\t\tlogin: " + QString(out.login)+    
         "\n\t\t\tpassword: "+out.password+ "}\n";
}
// DONE
QString Logger::Log_AddFriendInfo(AddFriendInfo& out) {
  return "\n\t\tAddFriendInfo{ requester_login: "+out.requester_login+
          "\n\t\t\trequester_id: "+ConvertQuint32ToString(out.requester_id) + " }\n";
}
// DONE
QString Logger::Log_FriendRequestInfo(FriendRequestInfo& out) {
  return "\n\tFriendRequestInfo{ other_login: " +out.other_login +
         "\n\t\t\tid: " + ConvertQuint32ToString(out.id) +
         "\n\t\t\tpassword: " + out.password + "}\n";
}
//test
QString Logger::Log_NewFriendInfo(NewFriendInfo& out) {
  
  return "\n\tNewFriendInfo{ IP: " + out.ip.toString() +
         "\n\t\t\tPort: " + ConvertQuint16ToString(out.port) +
         "\n\t\t\tID: " + ConvertQuint32ToString(out.id) +
         "\n\t\t\tLogin: " + QString(out.login) + " }\n";
} 

void Logger::RemoveShit(QString &stringd)
{
    std::vector<std::string>msg;
    std::string myText = stringd.toStdString();
    std::istringstream iss(myText);
    std::string token;
    while (std::getline(iss, token, ':'))
    {
      //
      msg.push_back(token);
    }
    QString Ip = QString::fromUtf8(msg[3].c_str());//only ip without ffff
    stringd = Ip + "::"+ QString::fromUtf8(msg[5].c_str());
}

QString Logger::Log_User(Client& cl) {
  QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
  return "User Login" + cl.GetUserName() + " ID:" + cl.GetUserId() +
         " IP:" + cl.GetUserIp().toString() + " Port:" + cl.GetUserPort() +
         "\n";
}
