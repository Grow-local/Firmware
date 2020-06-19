/*
 * File: ambientsensor.h
 * Project: include
 * File Created: Thursday, 26th March 2020 9:19:41
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday June 17th 2020 10:12:45
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef PLANT_SENSORS_AMBIENT_TEMPERATURE_SENSOR_H
#define PLANT_SENSORS_AMBIENT_TEMPERATURE_SENSOR_H

#include <Adafruit_AM2320.h>

#include "sensor.h"

class AmbientTemperatureSensor : public Sensor, public Adafruit_AM2320 {
public:
	AmbientTemperatureSensor() : Sensor("ambientTemperature") { }
	float ReadData() override;
};

#endif