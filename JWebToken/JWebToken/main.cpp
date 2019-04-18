#include <QtCore/QCoreApplication>
#include <iostream>
#include "WebToken.h"
#include <qdatastream.h>
int main(int argc, char *argv[]) {

  QCoreApplication a(argc, argv);
  WebToken wt;
  SpeckCypher sc;
  wt.SetHeader("SPEK");
  wt.SetPayload(1);
  std::string tok = wt.GetToken("ab301234aiEr12d4");
  std::cout << tok << std::endl;
  WebToken webt{tok};
  webt.ParseToken();
  std::cout << webt.IsSignatureValid("ab301234aiEr12d4");
  return a.exec();
}
