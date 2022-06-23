/*
 * Sensor.h
 */

#ifndef CLASSES_SENSOR_H_
#define CLASSES_SENSOR_H_

#include <Arduino.h>

// Sensors <= 10 is i2c, sensors > 10 need pin
enum sensor_type{
	VCC_SENSOR = 1,
	LIGHT_SENSOR,
	WEATHER_TEMPERATURE_SENSOR,
	WEATHER_HUMIDITY_SENSOR,
	WEATHER_PRESSURE_SENSOR,
	WATER_PRESSURE_SENSOR,
	WATER_LEAK_SENSOR = 11
};

class Sensor {
public:
	Sensor(byte sensorId);
	virtual ~Sensor(){}

	byte sensorId;

	virtual void start() = 0;
	virtual double getValue() = 0;
	virtual String getUnit() = 0;
};

#endif /* CLASSES_SENSOR_H_ */
