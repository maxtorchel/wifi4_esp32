/*
 * SensorManager.h
 */

#ifndef CLASSES_SENSORMANAGER_H_
#define CLASSES_SENSORMANAGER_H_

#include "Sensor.h"
#include "../settings/Settings.h"

class SensorManager {
public:
	SensorManager();

	Sensor* getSensor(byte sensorId);

private:
	Settings& _settings = Settings::Instance();
};

#endif /* CLASSES_SENSORMANAGER_H_ */
