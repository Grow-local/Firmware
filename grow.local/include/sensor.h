/*
 * File: sensor.h
 * Project: include
 * File Created: Thursday, 26th March 2020 9:14:45
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Thursday March 26th 2020 10:14:55
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef SENSOR_H
#define SENSOR_H

#include "config.h"

struct SensorData {
	float value;
	char timestamp[TIMESTAMP_LENGTH];
};

class Sensor {
public:
	virtual void RecordData(const char*) = 0;
	virtual void DataToJSONArray(char*) = 0;
};

#endif