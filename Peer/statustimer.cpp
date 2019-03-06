#include "statustimer.h"

StatusTimer::StatusTimer(QObject *parent)
	: QTimer(parent)
{
	connect(this, SIGNAL(timeout()), this, SLOT(EmitTimeoutById()));
}

StatusTimer::~StatusTimer()
{
}

unsigned StatusTimer::get_id() const
{
	return id;
}

void StatusTimer::set_id(quint32 id)
{
	this->id = id;
}

void StatusTimer::EmitTimeoutById()
{
	emit TimeoutById(id);
}
