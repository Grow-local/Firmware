/*
 * File: sensor.h
 * Project: include
 * File Created: Thursday, 26th March 2020 9:14:45
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday June 17th 2020 10:10:15
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef PLANT_SENSORS_SENSOR_H
#define PLANT_SENSORS_SENSOR_H

#include <ArduinoJson.h>
#include <time.h>

#include "config.h"

struct SensorData {
	float value;
	char timestamp[TIMESTAMP_LENGTH];
};

class Sensor {
public:
	Sensor(const char* label);
	virtual void RecordData(struct tm* timestamp);
	virtual void SaveToFile(File* file);
	virtual void ReadFromFile(File* file);
	virtual float ReadData() = 0;
	
protected:
	std::vector<SensorData> data_history;
	const char* label;
};

#endif