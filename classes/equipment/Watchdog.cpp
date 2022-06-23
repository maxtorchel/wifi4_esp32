/*
 * Watchdog.cpp
 */

#include <ESP32Ping.h>

#include "Watchdog.h"

Watchdog::Watchdog() {}

bool Watchdog::checkHost(char* host)
{
	if(!Ping.ping(host, 1)){
		if(try_counter>=_settings.config.watchdog.try_count){
			try_counter = 0;
			return false;
		}else
			try_counter++;
	}

	return true;
}
