#include <QtCore/QCoreApplication>
#include <iostream>
#include "sqldal.h"
using namespace SQLDAL;

int main(int argc, char *argv[]) {

  QCoreApplication a(argc, argv);

  UnitOfWork db;
  auto fr_rq = db.GetEntity<SQLDAL::FriendInfo>();
  fr_rq->Add(2, 3);
  return a.exec();
}
