#pragma once
#include <QByteArray>
#include <QString>
#include <QCryptographicHash>
#include <QDebug>
#include <QTextCodec>
class AbstractCypher
{
   public:
    virtual void Encrypt(QByteArray& plain_text, QString key) = 0;
    virtual void Decrypt(QByteArray& cypher_text, QString key) = 0;
   //protected:
    static QString HashString(QString); 

};
