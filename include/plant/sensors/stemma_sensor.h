/*
 * File: stemma_sensor.h
 * Project: include
 * File Created: Wednesday, 8th April 2020 12:35:31
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday June 17th 2020 10:12:58
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef PLANT_SENSORS_STEMMA_SENSOR_H
#define PLANT_SENSORS_STEMMA_SENSOR_H

#include <seesaw.h>

#include "sensor.h"

class StemmaSensor : public Sensor, public Adafruit_seesaw {
public:
	StemmaSensor();
	float ReadData() override;
};

#endif