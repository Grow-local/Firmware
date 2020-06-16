/*
 * File: stemma_sensor.h
 * Project: include
 * File Created: Wednesday, 8th April 2020 12:35:31
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday April 8th 2020 12:56:59
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef STEMMA_SENSOR_H
#define STEMMA_SENSOR_H

#include <seesaw.h>

#include "sensor.h"

class StemmaSensor : public Sensor, public Adafruit_seesaw {
public:
	void RecordData(struct tm* timestamp);
	void SaveToFile(File* file);
	void ReadFromFile(File* file);

	StemmaSensor();
private:
	std::vector<SensorData> moisture_history;
};

#endif