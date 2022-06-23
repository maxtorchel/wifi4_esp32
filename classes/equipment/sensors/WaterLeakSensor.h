/*
 * WaterLeakSensor.h
 */

#ifndef CLASSES_EQUIPMENT_SENSORS_WATERLEAKSENSOR_H_
#define CLASSES_EQUIPMENT_SENSORS_WATERLEAKSENSOR_H_

#include "../Sensor.h"
#include "RemoteSensor.h"
#include "../../settings/Settings.h"

class WaterLeakSensor : public Sensor {
public:
	WaterLeakSensor(byte sensorId);

	byte sensorId;

	void start();
	double getValue();
	String getUnit();

private:
	Settings& _settings = Settings::Instance();
};

#endif /* CLASSES_EQUIPMENT_SENSORS_WATERLEAKSENSOR_H_ */
