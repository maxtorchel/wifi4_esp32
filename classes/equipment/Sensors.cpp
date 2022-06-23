/*
 * Sensors.cpp
 */

#include "Sensors.h"

Sensors::Sensors() {}

void Sensors::startSensors()
{
	for(byte i=0;i<_settings.SENSORS_COUNT;i++){
		if(_settings.checkSensor(i)){
			std::unique_ptr<Sensor> sensor(_sensorManager.getSensor(i));
			sensor->start();
		}
	}
}

double Sensors::getSensorValue(byte sensorId)
{
	if(_settings.config.sensors.list[sensorId].type==0){
		Serial.println(F("Undefined sensor type!"));
		return -999;
	}else{
		std::unique_ptr<Sensor> sensor(_sensorManager.getSensor(sensorId));
		return sensor->getValue();
	}
}

String Sensors::getSensorUnit(byte sensorId)
{
	if(_settings.config.sensors.list[sensorId].type==0){
		Serial.println(F("Undefined sensor type!"));
		return "";
	}else{
		std::unique_ptr<Sensor> sensor(_sensorManager.getSensor(sensorId));
		return sensor->getUnit();
	}
}

void Sensors::handleSensors()
{
	handleSensorsLog();
}

void Sensors::handleSensorsLog()
{
	unsigned long curmillis = millis();
	static unsigned long log_timestamp[_settings.SENSORS_COUNT];

	if(curmillis - timestamp > 1000){
		timestamp = curmillis;

		for(byte i=0;i<_settings.SENSORS_COUNT;i++){
			unsigned int log_interval = _settings.config.sensors.list[i].log_interval;
			if(_settings.checkSensor(i) && log_interval>0){
				if(curmillis-log_timestamp[i]>1000*log_interval || log_timestamp[i]==0){
					log_timestamp[i] = curmillis;
					_log.write(F("sensor.log"),String(i+1)+","+String(getSensorValue(i)));
				}
			}else{
				log_timestamp[i] = 0;
			}
		}
	}
}
