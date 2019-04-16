#pragma once
#include <QString>
#include <QCryptographicHash>
#include <QDebug>
#include <QTextCodec>
#include <QObject>
#include <QByteArray>
#include <QDataStream>
#include <iostream>

using namespace std;
class AbstractCypher
{
   public:
    virtual void Encrypt(QByteArray& plain_text, QString key) = 0;
    virtual void Decrypt(QByteArray& cypher_text, QString key) = 0;
   //protected:
    static QString HashString(QString); 
    QByteArray ConvertStringToByteArr(QString);
    QString ConvertByteArrayToString(QByteArray);
};
