/*
 * Watchdog.h
 */

#ifndef CLASSES_WATCHDOG_H_
#define CLASSES_WATCHDOG_H_

#include "../settings/Settings.h"

class Watchdog {
public:
	Watchdog();

	bool checkHost(char* host);
private:
	Settings& _settings = Settings::Instance();
	byte try_counter = 0;
};

#endif /* CLASSES_WATCHDOG_H_ */
