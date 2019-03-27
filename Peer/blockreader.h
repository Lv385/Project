#ifndef BLOCKREADER_H
#define BLOCKREADER_H

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include <QByteArray>


#include "../Parser&Structs/parser.h"

class BlockReader : public QObject {
  Q_OBJECT

 public:
  BlockReader(QTcpSocket* socket);
  ~BlockReader();

  QByteArray ReadNextBlock();
  bool HasPendingBlock();
  bool WaitForReadyReadBlock();

signals:
  void ReadyReadBlock();

 private slots:
  void OnReadyRead();

 private:
  QList<QByteArray> blocks_;
  QByteArray data_;
  QTcpSocket* socket_;
  QByteArray unpossible_sequence_;
};

#endif  // !BLOCKREADER_H
