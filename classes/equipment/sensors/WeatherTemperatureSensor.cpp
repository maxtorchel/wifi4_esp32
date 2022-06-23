/*
 * WeatherTemperatureSensor.cpp
 */

#include "WeatherTemperatureSensor.h"

WeatherTemperatureSensor::WeatherTemperatureSensor(byte sensorId) : sensorId(sensorId), Sensor(sensorId) {}

void WeatherTemperatureSensor::start() {}

double WeatherTemperatureSensor::getValue()
{
	if(String(_settings.config.sensors.list[sensorId].host)==""){
		unsigned long curmillis = millis();
		if(curmillis - timestamp > 3000){
			timestamp = curmillis;

			if(_dht12.update()!=0){
				Serial.println(F("Weather temperature sensor read fails!"));
				_value = -999;
			}else
				_value = _dht12.temperatureC;
		}

		return _value;
	}else{
		RemoteSensor _remoteSensor(sensorId);
		return _remoteSensor.getValue();
	}
}

String WeatherTemperatureSensor::getUnit()
{
	return F("C");
}
