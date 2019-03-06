#pragma once

#include <QTimer>

class StatusTimer : public QTimer
{
	Q_OBJECT

public:
	StatusTimer(QObject *parent = 0);
	~StatusTimer();
	unsigned get_id() const;
	void set_id(quint32);

signals:
	void TimeoutById(quint32);

private slots:
	void EmitTimeoutById();

private:
	quint32 id;
};
