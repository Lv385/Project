#pragma once
#include "logger.h"


//nevermind about following

//QString Logger::Log_Empty(quint8 type)
//{
//   // should be ended // possibly by adding other map where value is a key map<value,bool> and it means is empty or not  
//  m[(quint8)ServerRequests::LOGIN_SUCCEED] = "LOGIN_SUCCEED";
//  m[(quint8)ServerRequests::LOGIN_FAILED] = "LOGIN_FAILED";
//  return  "  Server output: "+QString(m[type])+" ";
//}

// void Logger::WriteLogToFile(QString& filename, QString& text)
void Logger::WriteLogToFile(QString& text) {
  // QFile file(filename);
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
    QString outingString;  // date (d/m/y) time (h/m/s)
    QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
    quint8 type = Parser::getRequestType(raw_data);
    QString for_empty = "("+ConvertQuint8ToString(type) + ")" + txt + "+ empty{}";
    QString for_struct;
    switch (type) {
   
    case (quint8)ServerRequests::LOGIN_SUCCEED: {
      outingString = IpAndPort + "  Server output: " + QString("LOGIN_SUCCEED") + " " + for_empty;
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::LOGIN_FAILED: {
      outingString = IpAndPort + "  Server output: " + QString("LOGIN_FAILED") + " " + for_empty;
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::REGISTER_FAILED: {
      outingString = " Server output: REGISTER_FAILED( " + for_empty;
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::FRIEND_REQUEST_FAILED: {
      outingString = " Server output: FRIEND_REQUEST_FAILED( " + for_empty;
      qDebug().noquote() << outingString << '\n';
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::FRIEND_REQUEST_SUCCEED: {
      outingString = " Server output: FRIEND_REQUEST_SUCCEED( " + for_empty;
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ClientRequest::LOGIN: {
      LoginInfo out;
      out = Parser::ParseAsLoginInfo(raw_data);
      outingString =IpAndPort+ " Server output: LOGIN( " + Log_LoginInfo(out);
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ClientRequest::REGISTER: {
      RegisterInfo out;
      out = Parser::ParseAsRegisterInfo(raw_data);
      outingString = " Server output: REGISTER( " + Log_RegisterInfo(out);
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::REGISTER_SUCCEED: {
      RegisterSuccessInfo out;
      out = Parser::ParseAsRegisterSuccessInfo(raw_data);
      outingString = " Server  output: REGISTER_SUCCEED(" +
        ConvertQuint8ToString(type) + ")" +
        Log_RegisterSuccessInfo(out);

      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::ADD_FRIEND_REQUEST: {
      AddFriendInfo out;
      out = Parser::ParseAsAddFriendInfo(raw_data);
      outingString = " Server  output: ADD_FRIEND_REQUEST(" +
        ConvertQuint8ToString(type) + ")" +
        Log_AddFriendInfo(out);
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::FRIEND_UPDATE_INFO: {
      FriendUpdateInfo out;
      out = Parser::ParseAsFriendUpdateInfo(raw_data);
      outingString = " Server  output: FRIEND_UPDATE_INFO(" +
        ConvertQuint8ToString(type) + ") " +
        Log_FriendUpdateInfo(out);
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    case (quint8)ServerRequests::NEW_FRIEND_INFO: {
      NewFriendInfo out;
      out = Parser::ParseAsNewFriendInfo(raw_data);
      outingString = " Server  output:NEW_FRIEND_INFO (" +
        ConvertQuint8ToString(type) + ") " +
        Log_NewFriendInfo(out);
      qDebug().noquote() << outingString << "\n";
      WriteLogToFile(outingString);
      break;
    }
    }
  }
}
QString Logger::Log_RegisterSuccessInfo(RegisterSuccessInfo& out) {
  QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
  return "RegisterSuccessInfo{ ID:" + ConvertQuint32ToString(out.id) +
         " }" + txt + '\n';
}

QString Logger::Log_AddFriendInfo(AddFriendInfo& out) {
  QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
  return "AddFriendInfo{ id: " + ConvertQuint32ToString(out.requester_id) +
         ",  Login: " + out.requester_login + " }" + txt + '\n';
}

QString Logger::Log_FriendUpdateInfo(FriendUpdateInfo& out) {
  QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
  return "Friend_Update_Info{  ip: " + out.ip.toString() +
         ", Port: " + ConvertQuint16ToString(out.port) +
         ",  ID: " + ConvertQuint32ToString(out.id) + " }" + txt + '\n';
  return txt;
}

QString Logger::Log_LoginInfo(LoginInfo& out) {
  QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
  return "LoginInfo{ Loginner_ip:" + QString("") +
         " , Port: " + ConvertQuint16ToString(out.port) +
         " , Loginnner ID: " + ConvertQuint32ToString(out.id) +
         " , Loginner_Password:" + out.password + " }" + txt + '\n';
}

QString Logger::Log_RegisterInfo(RegisterInfo& out) {
  QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
  return "RegisterInfo{ Registerer_ip: " + QString("  ") +
         ", Port: " + ConvertQuint16ToString(out.port) +
         ", Registerer Login: " + QString(out.login) +
         ", Registerer_Password:" + out.password + "}" + txt + '\n';
}

QString Logger::Log_FriendRequestInfo(FriendRequestInfo& out) {
  QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
  return "Friend_Request_Info{ Other_Login: " + out.other_login +
         ", ID: " + ConvertQuint32ToString(out.id) +
         ", Password: " + QString(out.password) + " }" + txt + '\n';
}

QString Logger::Log_NewFriendInfo(NewFriendInfo& out) {
  QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
  return "NEW_FRIEND_INFO{ IP: " + out.ip.toString() +
         ", Port: " + ConvertQuint16ToString(out.port) +
         ", ID: " + ConvertQuint32ToString(out.id) +
         ", Login: " + QString(out.login) + " }" + txt + '\n';
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
    stringd = Ip + " :: "+ QString::fromUtf8(msg[5].c_str());
}

QString Logger::Log_User(Client& cl) {
  QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
  return "User Login" + cl.GetUserName() + " ID:" + cl.GetUserId() +
         " IP:" + cl.GetUserIp().toString() + " Port:" + cl.GetUserPort() +
         "\n";
}