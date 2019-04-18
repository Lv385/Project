#include "hashhelper.h"

QString hashhelper::HashString(const QString s) { 
  QByteArray ba = s.toUtf8();
  return QString::fromUtf8(QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex());
}
