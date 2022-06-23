/*
 * WeatherPressureSensor.cpp
 */

#include "WeatherPressureSensor.h"

WeatherPressureSensor::WeatherPressureSensor(byte sensorId) : sensorId(sensorId), Sensor(sensorId) {}

void WeatherPressureSensor::start() {}

double WeatherPressureSensor::getValue()
{
	if(String(_settings.config.sensors.list[sensorId].host)==""){
		if (!_bmp.begin()){
			Serial.println(F("Weather pressure sensor read fails!"));
			return -999;
		}else
			return _bmp.readPressure()*0.007501;
	}else{
		RemoteSensor _remoteSensor(sensorId);
		return _remoteSensor.getValue();
	}
}

String WeatherPressureSensor::getUnit()
{
	return F("mm");
}
