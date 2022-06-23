/*
 * Relay.h
 */

#ifndef CLASSES_RELAY_H_
#define CLASSES_RELAY_H_

#include <HTTPClient.h>

#include "Watchdog.h"
#include "../log/Log.h"

class Relay {
public:
	Relay();

	void switchRelay(byte relayId, byte state, boolean save = true);
	void initRelays();
	void handleWatchdog();
private:
	Settings& _settings = Settings::Instance();
	Watchdog _watchdog;
	Log _log;
	unsigned long timestamp = 0;

	void initRelay(byte relayId);
	bool switchRemoteRelay(byte relayId, byte state);
};

#endif /* CLASSES_RELAY_H_ */
