/*
 * Screen.h
 */

#ifndef CLASSES_EQUIPMENT_SCREEN_H_
#define CLASSES_EQUIPMENT_SCREEN_H_

#include <SSD1306Wire.h>

#include "../settings/Settings.h"
#include "Clock.h"
#include "Sensors.h"

enum source_type{CLOCK = 1, SENSOR};

class Screen {
public:
	Screen();

	const static byte POSITIONS_COUNT = 4;

	struct {
		unsigned int x;
		unsigned int y;
	} positions[POSITIONS_COUNT] = {
						   	   {0,0},
						   	   {0,16},
						   	   {0,32},
						   	   {0,48},
						   };

	SSD1306Wire ssd = SSD1306Wire(0x3c, SDA, SCL);

	void init();
	bool exists();
	void display();
	void displayHeader();
	void displayContent();

private:
	Settings& _settings = Settings::Instance();
	Clock _clock;
	Sensors _sensors;

	unsigned long timestamp = 0;
};

#endif /* CLASSES_EQUIPMENT_SCREEN_H_ */
