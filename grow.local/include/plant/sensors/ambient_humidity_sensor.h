/*
 * File: ambientsensor.h
 * Project: include
 * File Created: Thursday, 26th March 2020 9:19:41
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Tuesday June 16th 2020 10:22:41
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef AMBIENT_HUMIDITY_SENSOR_H
#define AMBIENT_HUMIDITY_SENSOR_H

#include <Adafruit_AM2320.h>

#include "sensor.h"

class AmbientHumiditySensor : public Sensor, public Adafruit_AM2320 {
public:
	AmbientHumiditySensor() : Sensor("humidity") { }
	float ReadData() override;
};

#endif