/*
 * WaterLeakSensor.cpp
 */

#include "WaterLeakSensor.h"

WaterLeakSensor::WaterLeakSensor(byte sensorId) : sensorId(sensorId), Sensor(sensorId) {}

void WaterLeakSensor::start()
{
	pinMode(_settings.config.sensors.list[sensorId].pin, INPUT_PULLUP); // set pin
}

double WaterLeakSensor::getValue()
{
	if(String(_settings.config.sensors.list[sensorId].host)==""){
		return digitalRead(_settings.config.sensors.list[sensorId].pin) ? 0 : 1; // inverting result
	}else{
		RemoteSensor _remoteSensor(sensorId);
		return _remoteSensor.getValue();
	}
}

String WaterLeakSensor::getUnit()
{
	return "";
}
