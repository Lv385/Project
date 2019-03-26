#include "abstractstrategy.h"

AbstractStrategy::AbstractStrategy(QObject *parent, PeerInfo peer_info,
                                   QByteArray data, QTcpSocket* socket)
    : QObject(parent)
    , peer_info_(peer_info)
    , data_(data)
    , k_unpossiblle_2_bytes_sequence_(Parser::GetUnpossibleSequence()){
}


AbstractStrategy::~AbstractStrategy() {}

