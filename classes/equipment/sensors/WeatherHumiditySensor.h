/*
 * WeatherHumiditySensor.h
 */

#ifndef CLASSES_WEATHERHUMIDITYSENSOR_H_
#define CLASSES_WEATHERHUMIDITYSENSOR_H_

#include <AM2320_asukiaaa.h>

#include "../Sensor.h"
#include "RemoteSensor.h"
#include "../../settings/Settings.h"

class WeatherHumiditySensor : public Sensor {
public:
	WeatherHumiditySensor(byte sensorId);

	byte sensorId;

	void start();
	double getValue();
	String getUnit();

private:
	Settings& _settings = Settings::Instance();

	AM2320_asukiaaa _dht12;

	unsigned long timestamp = 0;
	double _value = -999;
};

#endif /* CLASSES_WEATHERHUMIDITYSENSOR_H_ */
