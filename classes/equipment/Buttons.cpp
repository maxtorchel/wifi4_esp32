/*
 * Buttons.cpp
 */

#include "Buttons.h"

Buttons::Buttons() {}

void Buttons::startButtons()
{
	startRebootResetButton();
}
void Buttons::handleButtons()
{
	handleRebootResetButton();
}

void Buttons::startRebootResetButton()
{
	pinMode(RR_BUTTON_PIN ,INPUT_PULLUP); // set pin
	_rr_bounce.attach(RR_BUTTON_PIN);
	_rr_bounce.interval(5);
}

void Buttons::handleRebootResetButton()
{
	static unsigned long press_timestamp = 0;

	_rr_bounce.update();

	if (_rr_bounce.fell())
		press_timestamp = millis();
	else if(_rr_bounce.rose()){
		if((millis() - press_timestamp) > RESET_PRESS_TIME){
			Serial.println(F("Resetting..."));
			_board.reset();
		}else if((millis() - press_timestamp) > REBOOT_PRESS_TIME){
			Serial.println(F("Rebooting..."));
			_board.reboot();
		}else
			press_timestamp = 0;
	}

	if(press_timestamp>0 && (millis() - press_timestamp) > FRESET_PRESS_TIME){
		Serial.println(F("Factory resetting..."));
		_board.factoryReset();
	}
}
