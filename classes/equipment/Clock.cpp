/*
 * Clock.cpp
 */

#include "Clock.h"

Clock::Clock() : _ntpClient(_ntpUDP) {}

void Clock::begin()
{
    RTC.begin();
   	_ntpClient.begin();
}

void Clock::setNtpOffset(int offset)
{
	_settings.setNtpOffset(offset, true);
	setDateTime(_ntpClient.getEpochTime()+_settings.config.ntp.offset);
}

void Clock::setNtpUpdateInterval(unsigned int interval)
{
	_settings.setNtpUpdateInterval(interval, true);
}

void Clock::ntpUpdate()
{
	unsigned long curmillis = millis();
    if(_settings.config.ntp.value==1){
    	if(_lastNtpUpdate==0 || curmillis-_lastNtpUpdate>_settings.config.ntp.interval){
    		_lastNtpUpdate = curmillis;
			if(_ntpClient.forceUpdate())
				setDateTime(_ntpClient.getEpochTime()+_settings.config.ntp.offset);
		}
    }
}

void Clock::setDateTime(unsigned long unixtime)
{
	DateTime dt(unixtime);
	setDate(dt);
	setTime(dt);
}

void Clock::setDate(DateTime dt)
{
	DateTime now = RTC.now();
	RTC.adjust(DateTime(
		dt.year(),
		dt.month(),
		dt.day(),
		now.hour(),
		now.minute(),
		now.second()
	));
}
void Clock::setTime(DateTime dt)
{
	DateTime now = RTC.now();
	RTC.adjust(DateTime(
		now.year(),
		now.month(),
		now.day(),
		dt.hour(),
		dt.minute()
	));
}

DateTime Clock::getDateTime(unsigned long unixtime /*= 0*/)
{
	if(unixtime!=0){
		DateTime dt(unixtime);
		return dt;
	}else
		return RTC.now();
}
String Clock::getDateString(unsigned long unixtime /*= 0*/)
{
	DateTime dt;
	dt = getDateTime(unixtime);
	return formatDigit(dt.day())+"."+formatDigit(dt.month())+"."+formatDigit(dt.year());
}
String Clock::getTimeString(unsigned long unixtime /*= 0*/, bool seconds /*= false*/)
{
	DateTime dt;
	dt = getDateTime(unixtime);
	return formatDigit(dt.hour())+":"+formatDigit(dt.minute())+(seconds?":"+formatDigit(dt.second()):"");
}
String Clock::getDateTimeString(unsigned long unixtime /*= 0*/, bool seconds /*= false*/)
{
	return getDateString(unixtime)+" "+getTimeString(unixtime, seconds);
}
String Clock::formatDigit(unsigned int digit)
{
	return digit<10?"0"+String(digit):String(digit);
}

bool Clock::exists()
{
	DateTime dt = getDateTime();
	return (dt.day()<=31 && dt.month()<=12 && dt.year()<=2050);
}
