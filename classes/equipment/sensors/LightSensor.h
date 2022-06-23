/*
 * LightSensor.h
 */

#ifndef CLASSES_LIGHTSENSOR_H_
#define CLASSES_LIGHTSENSOR_H_

#include <MAX44009.h>

#include "../Sensor.h"
#include "RemoteSensor.h"
#include "../../settings/Settings.h"

class LightSensor : public Sensor {
public:
	LightSensor(byte sensorId);

	byte sensorId;

	void start();
	double getValue();
	String getUnit();

private:
	Settings& _settings = Settings::Instance();

    MAX44009 _light;
};

#endif /* CLASSES_LIGHTSENSOR_H_ */
