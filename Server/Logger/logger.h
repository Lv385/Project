#pragma once
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <vector>
#include <string>
#include <sstream>
#include <QTextStream>
#include <QTcpSocket>
#include <QIODevice>
#include "../Parser&Structs/parser.h"
#include "DAL/Client.h"

#define stringify( name ) # name

class Logger {
 static bool const ifLogingEnable = true;
 public:
   static void LogOut(QString&, QByteArray);
   static QString Log_User(Client &cl);
   static QString ConvertQuint8ToString(quint8 num);
   static QString ConvertQuint16ToString(quint16  num);
   static QString ConvertQuint32ToString(quint32  num);
 private:
   //static void WriteLogToFile(QString&,QString&);
  // static QString Log_Empty(quint8 type);
   static void WriteLogToFile(QString&);
   static QString Log_RegisterSuccessInfo(RegisterSuccessInfo &out);
   static QString Log_AddFriendInfo(AddFriendInfo &out);
   static QString Log_FriendUpdateInfo(FriendUpdateInfo &out);
   static QString Log_LoginInfo(LoginInfo &out);
   static QString Log_RegisterInfo(RegisterInfo&out);
   static QString Log_FriendRequestInfo(FriendRequestInfo &out);   
   static QString Log_NewFriendInfo(NewFriendInfo &out);
   static void RemoveShit(QString &stringd);
   
   //static std::map<quint8, QString> m;

};
