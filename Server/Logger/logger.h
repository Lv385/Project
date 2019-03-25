#pragma once
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include "../Parser&Structs/parser.h"
#include "DAL/Client.h"
class Logger {
 static bool const ifLogingEnable = true;
 public:
   static void LogOut(QByteArray);
   static QString Log_User(Client &cl);
 private:
   //static void WriteLogToFile(QString&,QString&);
   static void WriteLogToFile(QString&);
   static QString ConvertQuint8ToString(quint8& num);
   static QString ConvertQuint16ToString(quint16 & num);
   static QString ConvertQuint32ToString(quint32 & num);  
   static QString Log_REGISTER_SUCCEED(RegisterSuccessInfo &out);
   static QString Log_ADD_FRIEND_REQUEST(AddFriendInfo &out);
   static QString Log_FRIEND_UPDATE_INFO(FriendUpdateInfo &out);
   static QString Log_LoginInfo(LoginInfo &out);
   static QString Log_RegisterInfo(RegisterInfo&out);
   static QString Log_FriendRequestInfo(FriendRequestInfo &out);   
};
