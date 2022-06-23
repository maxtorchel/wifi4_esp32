/*
 * WaterPressureSensor.cpp
 */

#include "WaterPressureSensor.h"

WaterPressureSensor::WaterPressureSensor(byte sensorId) : sensorId(sensorId), Sensor(sensorId) {}

void WaterPressureSensor::start() {}

double WaterPressureSensor::getValue()
{
	if(String(_settings.config.sensors.list[sensorId].host)==""){
		int sensorVal = analogRead(_PIN);
		float voltage = (sensorVal*3.3)/1024.0;
		float pressure_pascal = (3.0*((float)voltage-0.45))*1000000.0;
		float pressure_bar = pressure_pascal/10e5;

		if(pressure_bar<-1){
			Serial.println(F("Water pressure sensor read fails!"));
			return -999;
		}else
			return pressure_bar<0?0:pressure_bar;
	}else{
		RemoteSensor _remoteSensor(sensorId);
		return _remoteSensor.getValue();
	}
}

String WaterPressureSensor::getUnit()
{
	return F("bar");
}
