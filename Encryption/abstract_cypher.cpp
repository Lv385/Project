#include "abstract_cypher.h"


QString AbstractCypher::HashString(QString s)
{
  QByteArray ba = s.toUtf8();
  QByteArray hashed_arr =QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex();
  QString DataAsString = QTextCodec::codecForMib(1015)->toUnicode(hashed_arr);
  return DataAsString;
}
