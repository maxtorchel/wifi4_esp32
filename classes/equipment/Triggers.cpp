/*
 * Triggers.cpp
 */

#include "Triggers.h"

Triggers::Triggers() {}

void Triggers::handleTriggers()
{
	unsigned long curmillis = millis();
	if(curmillis - timestamp > 1000){
		timestamp = curmillis;

		for(byte i=0;i<_settings.TRIGGERS_COUNT;i++){
			if(_settings.checkTrigger(i)){
				byte sensorId = _settings.config.triggers.list[i].sensor-1;
				double value = _sensors.getSensorValue(sensorId);
				double on_value = _settings.config.triggers.list[i].on_value;
				double off_value = _settings.config.triggers.list[i].off_value;
				byte targetId = _settings.config.triggers.list[i].target_number-1;

				switch (_settings.config.triggers.list[i].target_type){
					case RELAY:{
						if(_settings.checkRelay(targetId)){
							bool relayState = _settings.config.relays.list[targetId].state;
							if(on_value>off_value){
								if(value!=-999 && value>on_value && !relayState){
									_relay.switchRelay(targetId, 1);
									_log.write(F("relay.log"), "R"+String(targetId+1)+" on by T"+String(i+1)+", S"+String(sensorId+1)+" value "+String(value)+">"+String(on_value)+".");
								}else if(value!=-999 && value<off_value && relayState){
									_relay.switchRelay(targetId, 0);
									_log.write(F("relay.log"), "R"+String(targetId+1)+" off by T"+String(i+1)+", S"+String(sensorId+1)+" value "+String(value)+"<"+String(off_value)+".");
								}
							}else{
								if(value!=-999 && value<on_value && !relayState){
									_relay.switchRelay(targetId, 1);
									_log.write(F("relay.log"), "R"+String(targetId+1)+" on by T"+String(i+1)+", S"+String(sensorId+1)+" value "+String(value)+"<"+String(on_value)+".");
								}else if(value!=-999 && value>off_value && relayState){
									_relay.switchRelay(targetId, 0);
									_log.write(F("relay.log"), "R"+String(targetId+1)+" off by T"+String(i+1)+", S"+String(sensorId+1)+" value "+String(value)+">"+String(off_value)+".");
								}
							}
						}else
							_log.write(F("relay.log"), "Can not switch R"+String(targetId+1)+" by T"+String(i+1)+" because it is disabled.");
					}
					break;
					case SCHEDULER:{
						if(_settings.checkSchedule(targetId)){
							bool shedulerState = _settings.config.scheduler.list[targetId].start_time;
							DateTime dt = _clock.getDateTime();
							if(on_value>off_value){
								if(value!=-999 && value>on_value && !shedulerState){
									_settings.setScheduleStartTime(targetId, dt.unixtime(), true);
									_log.write(F("scheduler.log"), "SC"+String(targetId+1)+" started by T"+String(i+1)+", S"+String(sensorId+1)+" value "+String(value)+">"+String(on_value)+".");
								}else if(value!=-999 && value<off_value && shedulerState){
									_settings.setScheduleStartTime(targetId, 0, true);
									_log.write(F("scheduler.log"), "SC"+String(targetId+1)+" stopped by T"+String(i+1)+", S"+String(sensorId+1)+" value "+String(value)+"<"+String(off_value)+".");
								}
							}else{
								if(value!=-999 && value<on_value && !shedulerState){
									_settings.setScheduleStartTime(targetId, dt.unixtime(), true);
									_log.write(F("scheduler.log"), "SC"+String(targetId+1)+" started by T"+String(i+1)+", S"+String(sensorId+1)+" value "+String(value)+"<"+String(on_value)+".");
								}else if(value!=-999 && value>off_value && shedulerState){
									_settings.setScheduleStartTime(targetId, 0, true);
									_log.write(F("scheduler.log"), "SC"+String(targetId+1)+" stopped by T"+String(i+1)+", S"+String(sensorId+1)+" value "+String(value)+">"+String(off_value)+".");
								}
							}
						}else
							_log.write(F("scheduler.log"), "Can not start/stop SC"+String(targetId+1)+" by T"+String(i+1)+" because it is disabled.");
					}
					break;
					default:
						Serial.println(F("Wrong trigger target type!"));
				}
			}
		}
	}
}
