#ifndef BLOCKWRITER_H
#define BLOCKWRITER_H

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include <QByteArray>
#include "../Parser&Structs/parser.h"

class BlockWriter : public QObject {
  Q_OBJECT

 public:
  BlockWriter(QTcpSocket* socket);
  ~BlockWriter();
  void set_socket(QTcpSocket* socket);
  void WriteBlock(QByteArray data);

 private:
  QTcpSocket* socket_;
  QByteArray unpossible_sequence_;
};

#endif  // !BLOCKWRITER_H
