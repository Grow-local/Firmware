/*
 * File: ambientsensor.h
 * Project: include
 * File Created: Thursday, 26th March 2020 9:19:41
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Thursday March 26th 2020 9:43:20
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef AMBIENTSENSOR_H
#define AMBIENTSENSOR_H

#include <Adafruit_AM2320.h>

#include "sensor.h"

class AmbientSensor : public Sensor, public Adafruit_AM2320 {
public:
	void RecordData(const char* timestamp);
	void DataToJSONArray(char* json);
private:
	std::vector<SensorData> temperature_history;
	std::vector<SensorData> humidity_history;
};

#endif