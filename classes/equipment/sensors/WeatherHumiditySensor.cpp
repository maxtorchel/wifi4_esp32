/*
 * WeatherHumiditySensor.cpp
 */

#include "WeatherHumiditySensor.h"

WeatherHumiditySensor::WeatherHumiditySensor(byte sensorId) : sensorId(sensorId), Sensor(sensorId) {}

void WeatherHumiditySensor::start() {}

double WeatherHumiditySensor::getValue()
{
	if(String(_settings.config.sensors.list[sensorId].host)==""){
		unsigned long curmillis = millis();
		if(curmillis - timestamp > 3000){
			timestamp = curmillis;

			if(_dht12.update()!=0){
				Serial.println(F("Weather humidity sensor read fails!"));
				_value = -999;
			}else
				_value = _dht12.humidity;
		}

		return _value;
	}else{
		RemoteSensor _remoteSensor(sensorId);
		return _remoteSensor.getValue();
	}
}

String WeatherHumiditySensor::getUnit()
{
	return F("%");
}
