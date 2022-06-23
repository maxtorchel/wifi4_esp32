/*
 * WeatherPressureSensor.h
 */

#ifndef CLASSES_WEATHERPRESSURESENSOR_H_
#define CLASSES_WEATHERPRESSURESENSOR_H_

#include <Adafruit_BMP085.h>

#include "../Sensor.h"
#include "RemoteSensor.h"
#include "../../settings/Settings.h"

class WeatherPressureSensor : public Sensor {
public:
	WeatherPressureSensor(byte sensorId);

	byte sensorId;

	void start();
	double getValue();
	String getUnit();

private:
	Settings& _settings = Settings::Instance();

	Adafruit_BMP085 _bmp;
};

#endif /* CLASSES_WEATHERPRESSURESENSOR_H_ */
