/*
 * Triggers.h
 */

#ifndef CLASSES_TRIGGERS_H_
#define CLASSES_TRIGGERS_H_

#include "../settings/Settings.h"
#include "Sensors.h"
#include "Relay.h"
#include "Clock.h"
#include "../log/Log.h"

enum target_type{RELAY = 1, SCHEDULER};

class Triggers {
public:
	Triggers();

	void handleTriggers();

private:
	Settings& _settings = Settings::Instance();
	Sensors _sensors;
	Relay _relay;
	Log _log;
	Clock _clock;
	unsigned long timestamp = 0;
};

#endif /* CLASSES_TRIGGERS_H_ */
