/*
 * WaterPressureSensor.h
 */

#ifndef CLASSES_WATERPRESSURESENSOR_H_
#define CLASSES_WATERPRESSURESENSOR_H_

#include "../Sensor.h"
#include "RemoteSensor.h"
#include "../../settings/Settings.h"

class WaterPressureSensor : public Sensor {
public:
	WaterPressureSensor(byte sensorId);

	byte sensorId;

	void start();
	double getValue();
	String getUnit();

private:
	Settings& _settings = Settings::Instance();

//	byte const _PIN = A0;
};

#endif /* CLASSES_WATERPRESSURESENSOR_H_ */
