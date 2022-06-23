/*
 * Clock.h
 */

#ifndef CLASSES_CLOCK_H_
#define CLASSES_CLOCK_H_

#include <Wire.h>
#include <RTClib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "../settings/Settings.h"


class Clock {
public:
	Clock();

	RTC_DS3231 RTC;

	void begin();
	void setNtpOffset(int offset);
	void setNtpUpdateInterval(unsigned int interval);
	void ntpUpdate();
	void setDateTime(unsigned long unixtime);
	void setDate(DateTime dt);
	void setTime(DateTime dt);
	DateTime getDateTime(unsigned long unixtime = 0);
	String getDateString(unsigned long unixtime = 0);
	String getTimeString(unsigned long unixtime = 0, bool seconds = false);
	String getDateTimeString(unsigned long unixtime = 0, bool seconds = false);
	bool exists();
private:
	Settings& _settings = Settings::Instance();

	unsigned long _lastNtpUpdate = 0;
	WiFiUDP _ntpUDP;
    NTPClient _ntpClient;

	String formatDigit(unsigned int digit);
};

#endif /* CLASSES_CLOCK_H_ */
