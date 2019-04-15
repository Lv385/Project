#include <QtCore/QCoreApplication>
#include <iostream>
#include "WebToken.h"
#include <qdatastream.h>
int main(int argc, char *argv[]) {

  QCoreApplication a(argc, argv);
  WebToken wt;
  wt.SetHeader("SPEK");
  wt.SetPayload(1);
  SpeckCypher sc;
  std::string key = "ab301234aiEr12d4";
  QString mystr = "45354354354";
  QByteArray text(mystr.toUtf8());
  QString keyQ = QString::fromUtf8(key.c_str());

  sc.Encrypt(text, keyQ);
  sc.Decrypt(text, keyQ);

  QDataStream in(&text, QIODevice::ReadOnly);
  QString s = text;
  std::cout << s.toStdString();

  return a.exec();
}
