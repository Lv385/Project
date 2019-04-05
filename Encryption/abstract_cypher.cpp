#include "abstract_cypher.h"


QString AbstractCypher::HashString(QString s)
{
  QByteArray ba = s.toUtf8();
  QByteArray hashed_arr = QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex();
  QString str = QString::fromUtf8(hashed_arr);
  return str;
}
