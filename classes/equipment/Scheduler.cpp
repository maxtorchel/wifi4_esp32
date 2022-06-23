/*
 * Scheduler.cpp
 */

#include "Scheduler.h"

Scheduler::Scheduler() {}

void Scheduler::handleScheduler()
{
	unsigned long curmillis = millis();
	if(curmillis - _timestamp > 1000 && _clock.exists()){
		_timestamp = curmillis;

		unsigned long time = _clock.getDateTime().unixtime();
		for(byte i=0;i<_settings.SCHEDULER_COUNT;i++){
			if(_settings.checkSchedule(i)){
				unsigned long start_time = _settings.config.scheduler.list[i].start_time;
				unsigned int on_seconds = _settings.config.scheduler.list[i].on_seconds;
				unsigned int off_seconds = _settings.config.scheduler.list[i].off_seconds;
				byte repeat = _settings.config.scheduler.list[i].repeat;
				byte relayId = _settings.config.scheduler.list[i].relay-1;
				byte relayState = _settings.config.relays.list[relayId].state;

				if(start_time<=time){
					unsigned int diff_seconds = time-start_time;
					unsigned int cycle_seconds = on_seconds+off_seconds;
					unsigned int cycles = (int)diff_seconds/cycle_seconds;
					unsigned int seconds = diff_seconds-cycle_seconds*cycles;

					if((cycles>0 && repeat==1) || cycles==0){
						if(seconds<on_seconds){
							if(relayState!=1){
								_relay.switchRelay(relayId, 1);
								_log.write(F("relay.log"), "R"+String(relayId+1)+" on by Scheduler S"+String(i+1)+".");
							}
						}else{
							if(relayState==1){
								_relay.switchRelay(relayId, 0);
								_log.write(F("relay.log"), "R"+String(relayId+1)+" off by Scheduler S"+String(i+1)+".");
							}
						}
					}
				}
			}
		}
	}
}
