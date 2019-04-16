#include "abstract_cypher.h"


QString AbstractCypher::HashString(QString s)
{
  QByteArray ba = s.toUtf8();
  QByteArray hashed_arr = QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex();
  QString str = QString::fromUtf8(hashed_arr);
  return str;
}

QByteArray AbstractCypher::ConvertStringToByteArr(QString string)
{
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << string;
  return result;
}

QString AbstractCypher::ConvertByteArrayToString(QByteArray data)
{
  QString str;
  QDataStream in(&data, QIODevice::ReadOnly);
  in >> str;
  return str;
}
