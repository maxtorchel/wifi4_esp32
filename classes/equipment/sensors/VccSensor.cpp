/*
 * VccSensor.cpp
 */

#include "VccSensor.h"

//ADC_MODE(ADC_VCC); //need for getVcc()

VccSensor::VccSensor(byte sensorId) : sensorId(sensorId), Sensor(sensorId) {}

void VccSensor::start() {}

double VccSensor::getValue()
{
//	double vcc = ESP.getVcc();
//	if(vcc>10000){
//		Serial.println(F("Vcc sensor read fails!"));
		return -999;
//	}else
//		return vcc/1000;
}
String VccSensor::getUnit()
{
	return F("V");
}
