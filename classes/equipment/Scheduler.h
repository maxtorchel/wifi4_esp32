/*
 * Scheduler.h
 */

#ifndef CLASSES_SCHEDULER_H_
#define CLASSES_SCHEDULER_H_

#include "../settings/Settings.h"
#include "Relay.h"
#include "Clock.h"
#include "../log/Log.h"

class Scheduler {
public:
	Scheduler();

	void handleScheduler();

private:
	Settings& _settings = Settings::Instance();
	Relay _relay;
	Clock _clock;
	Log _log;
	unsigned long _timestamp = 0;
};

#endif /* CLASSES_SCHEDULER_H_ */
