/*
 * VccSensor.h
 */

#ifndef CLASSES_VCCSENSOR_H_
#define CLASSES_VCCSENSOR_H_

#include "../Sensor.h"

class VccSensor : public Sensor {
public:
	VccSensor(byte sensorId);

	byte sensorId;

	void start();
	double getValue();
	String getUnit();
};

#endif /* CLASSES_VCCSENSOR_H_ */
