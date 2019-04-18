#ifndef HASHHELPER_H
#define HASHHELPER_H

#include <QByteArray>
#include <QString>
#include <QCryptographicHash>

namespace hashhelper {
  QString HashString(const QString s);
};

#endif  // !HASHHELPER_H
