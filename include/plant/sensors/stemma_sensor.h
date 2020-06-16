/*
 * File: stemma_sensor.h
 * Project: include
 * File Created: Wednesday, 8th April 2020 12:35:31
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Tuesday June 16th 2020 10:24:49
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
	StemmaSensor();
	float ReadData() override;
};

#endif