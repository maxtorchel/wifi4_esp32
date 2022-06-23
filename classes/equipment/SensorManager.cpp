/*
 * SensorManager.cpp
 */

#include "SensorManager.h"

#include "sensors/LightSensor.h"
//#include "sensors/VccSensor.h"
#include "sensors/WeatherTemperatureSensor.h"
#include "sensors/WeatherHumiditySensor.h"
#include "sensors/WeatherPressureSensor.h"
#include "sensors/WaterPressureSensor.h"
#include "sensors/WaterLeakSensor.h"

SensorManager::SensorManager() {}

Sensor* SensorManager::getSensor(byte sensorId)
{
	Sensor* sensor = NULL;
	byte type = _settings.config.sensors.list[sensorId].type;

	switch (type){
		case LIGHT_SENSOR:
			sensor = new LightSensor(sensorId);
			return sensor;
//		case VCC_SENSOR:
//			sensor = new VccSensor;
//			return sensor;
		case WEATHER_TEMPERATURE_SENSOR:
			sensor = new WeatherTemperatureSensor(sensorId);
			return sensor;
		case WEATHER_HUMIDITY_SENSOR:
			sensor = new WeatherHumiditySensor(sensorId);
			return sensor;
		case WEATHER_PRESSURE_SENSOR:
			sensor = new WeatherPressureSensor(sensorId);
			return sensor;
		case WATER_PRESSURE_SENSOR:
			sensor = new WaterPressureSensor(sensorId);
			return sensor;
		case WATER_LEAK_SENSOR:
			sensor = new WaterLeakSensor(sensorId);
			return sensor;
		default:
			Serial.println(F("Wrong sensor type!"));
			return sensor;
	}
}
