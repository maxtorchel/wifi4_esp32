/*
 * RemoteSensor.cpp
 */

#include "RemoteSensor.h"

RemoteSensor::RemoteSensor(byte sensorId) : sensorId(sensorId), Sensor(sensorId) {}

void RemoteSensor::start() {}

double RemoteSensor::getValue()
{
	String val = F("-999");
	HTTPClient http;
	http.begin(_settings.config.sensors.list[sensorId].host, _settings.config.port.value, "/sensor?id="+String(sensorId));
	http.setAuthorization(_settings.config.login.value, _settings.config.password.value);
	if(http.GET() == HTTP_CODE_OK)
		val = http.getString();
	http.end();

	return val.toFloat();
}

String RemoteSensor::getUnit()
{
	return "";
}
