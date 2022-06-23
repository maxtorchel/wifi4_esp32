/*
 * Buttons.h
 */

#ifndef CLASSES_BUTTONS_H_
#define CLASSES_BUTTONS_H_

#include <Arduino.h>
#include <Bounce2.h>

#include "Board.h"

class Buttons {
public:
	Buttons();

	void startButtons();
	void handleButtons();
private:
	Board _board;

	//Reboot && Reset button
	const static byte RR_BUTTON_PIN = 39;
	const static unsigned int FRESET_PRESS_TIME = 20000;
	const static unsigned int RESET_PRESS_TIME = 5000;
	const static unsigned int REBOOT_PRESS_TIME = 1000;

	Bounce _rr_bounce  = Bounce();

	void startRebootResetButton();
	void handleRebootResetButton();
};

#endif /* CLASSES_BUTTONS_H_ */
