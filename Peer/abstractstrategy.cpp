#include "abstractstrategy.h"
#include "signalredirector.h"


AbstractStrategy::AbstractStrategy(PeerInfo peer_info) : 
  peer_info_(peer_info),
  redirector_(SignalRedirector::get_instance()) {
  }


AbstractStrategy::~AbstractStrategy() {
}

