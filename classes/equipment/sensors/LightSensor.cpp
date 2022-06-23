/*
 * LightSensor.cpp
 */

#include "LightSensor.h"

LightSensor::LightSensor(byte sensorId) : sensorId(sensorId), Sensor(sensorId) {}

void LightSensor::start() {}

double LightSensor::getValue()
{
	if(String(_settings.config.sensors.list[sensorId].host)==""){
		_light.begin();
		float lux = _light.get_lux();
		if(lux>376012){
			Serial.println(F("Light sensor read fails!"));
			return -999;
		}else
			return _light.get_lux();
	}else{
		RemoteSensor _remoteSensor(sensorId);
		return _remoteSensor.getValue();
	}
}

String LightSensor::getUnit()
{
	return F("lx");
}
