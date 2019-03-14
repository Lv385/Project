#pragma once
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include "../Parser&Structs/parser.h"

class Logger {
 static bool const ifLogingEnable = true;
 public:
   static void WriteLogToFile(QString&,QString&);
   static void log(QByteArray&);   
   
};
