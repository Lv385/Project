#pragma once
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include "../Parser&Structs/parser.h"

class Logger {
 static bool const ifLogingEnable = true;
 public:
   static void WriteLogToFile(QString&,QString&);
   static QString ConvertQuint8ToString(quint8& num);
   static void log(QByteArray);   
   
};
