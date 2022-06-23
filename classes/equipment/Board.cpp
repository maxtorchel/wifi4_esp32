/*
 * Board.cpp
 */

#include <FS.h>
#include <SPIFFS.h>

#include "Board.h"

Board::Board() {}

void Board::begin()
{
	clock.begin();
	screen.init();
}

void Board::reboot(unsigned int milliseconds /*=1*/)
{
	delay(milliseconds);
	_log.write(F("board.log"), F("Reboot."));
	ESP.restart();
}

void Board::reset(unsigned int milliseconds /*=1*/)
{
	delay(milliseconds);
	_settings.resetConfig();
	_log.write(F("board.log"), F("Reset settings."));
	reboot();
}

void Board::factoryReset(unsigned int milliseconds /*=1*/)
{
	delay(milliseconds);
	SPIFFS.format();
	_log.write(F("board.log"), F("Factory reset."));
	reboot();
}

bool Board::i2cDeviceExists(byte address)
{
	//wakeup sensor
    Wire.beginTransmission(address);
    Wire.endTransmission();
    //check
    Wire.beginTransmission(address);
    return Wire.endTransmission()==0;
}
