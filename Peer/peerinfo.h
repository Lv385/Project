#ifndef PEERINFO_H
#define PEERINFO_H

#include <QString>
#include <QHostAddress>


struct PeerInfo
{
  quint32 id;
  QString login;
  QHostAddress ip;
  quint16 port;
  bool is_online;
};

#endif // !PEERINFO_H
