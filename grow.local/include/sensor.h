/*
 * File: sensor.h
 * Project: include
 * File Created: Thursday, 26th March 2020 9:14:45
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Thursday March 26th 2020 17:22:44
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <ArduinoJson.h>
#include <time.h>

#include "config.h"

struct SensorData {
	float value;
	char timestamp[TIMESTAMP_LENGTH];
};

class Sensor {
public:
	virtual void RecordData(struct tm*) = 0;
	virtual void SaveToFile(File*) = 0;
	virtual void ReadFromFile(File*) = 0;
};

#endif