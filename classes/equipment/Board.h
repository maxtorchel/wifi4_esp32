/*
 * Board.h
 */

#ifndef CLASSES_BOARD_H_
#define CLASSES_BOARD_H_

#include <Arduino.h>

#include "Clock.h"
#include "Relay.h"
#include "Sensors.h"
#include "Screen.h"
#include "../log/Log.h"

class Board {
public:
	Board();

	Clock clock;
	Relay relay;
	Sensors sensors;
	Screen screen;

	void begin();
	void reboot(unsigned int milliseconds = 1);
	void reset(unsigned int milliseconds = 1);
	void factoryReset(unsigned int milliseconds = 1);
	bool i2cDeviceExists(byte address);
private:
	Settings& _settings = Settings::Instance();
	Log _log;
};

#endif /* CLASSES_BOARD_H_ */
