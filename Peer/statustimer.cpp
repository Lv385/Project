#include "statustimer.h"

StatusTimer::StatusTimer(QObject *parent) : QTimer(parent) {
  connect(this, SIGNAL(timeout()), this, SLOT(EmitTimeoutById()));
}

StatusTimer::~StatusTimer() {}

unsigned StatusTimer::get_id() const { return id_; }

void StatusTimer::set_id(quint32 id) { id_ = id; }

//#tofix emiting slot
void StatusTimer::EmitTimeoutById() { emit TimeoutById(id_); }
