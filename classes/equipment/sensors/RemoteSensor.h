/*
 * RemoteSensor.h
 */

#ifndef CLASSES_REMOTESENSOR_H_
#define CLASSES_REMOTESENSOR_H_

#include <HTTPClient.h>

#include "../Sensor.h"
#include "../../settings/Settings.h"

class RemoteSensor : public Sensor {
public:
	RemoteSensor(byte sensorId);

	byte sensorId;

	void start();
	double getValue();
	String getUnit();

private:
	Settings& _settings = Settings::Instance();
};

#endif /* CLASSES_REMOTESENSOR_H_ */
