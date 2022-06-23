/*
 * Sensors.h
 */

#ifndef CLASSES_SENSORS_H_
#define CLASSES_SENSORS_H_

#include "../settings/Settings.h"
#include "SensorManager.h"
#include "../log/Log.h"

class Sensors {
public:
	Sensors();

	void startSensors();
	double getSensorValue(byte sensorId);
	String getSensorUnit(byte sensorId);
	void handleSensors();
	void handleSensorsLog();

private:
	Settings& _settings = Settings::Instance();
	SensorManager _sensorManager;
	Log _log;
	unsigned long timestamp = 0;
};

#endif /* CLASSES_SENSORS_H_ */
