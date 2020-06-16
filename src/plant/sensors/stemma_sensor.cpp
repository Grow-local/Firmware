/*
 * File: stemma_sensor.cpp
 * Project: src
 * File Created: Wednesday, 8th April 2020 12:35:11
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Tuesday June 16th 2020 10:24:56
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "plant/sensors/stemma_sensor.h"

StemmaSensor::StemmaSensor() : Sensor("soilMoisture") {
	this->begin(0x36);
}

float StemmaSensor::ReadData() {
	return this->touchRead(0);
}