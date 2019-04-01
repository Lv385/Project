#pragma once
#include <QByteArray>
#include <QString>
#include <QCryptographicHash>
#include <QDebug>
#include <QTextCodec>
class AbstractCypher
{
   public:
    //  virtual QByteArray Encrypt(QByteArray) = 0;
     // virtual QByteArray Decrypt(QByteArray) = 0;
   //protected:
    static QString HashString(QString); // should be protected

};