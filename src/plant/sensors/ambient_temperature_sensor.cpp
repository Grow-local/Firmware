/*
 * File: ambientsensor.cpp
 * Project: src
 * File Created: Thursday, 26th March 2020 9:21:17
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Tuesday June 16th 2020 10:23:54
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "plant/sensors/ambient_temperature_sensor.h"

float AmbientTemperatureSensor::ReadData() { return this->readTemperature(); }