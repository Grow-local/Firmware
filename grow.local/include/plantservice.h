/*
 * File: plantservice.h
 * Project: include
 * File Created: Tuesday, 24th March 2020 18:20:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Thursday April 9th 2020 16:00:49
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef PLANTSERVICE_H
#define PLANTSERVICE_H

#define _TASK_TIMEOUT 
#define _TASK_OO_CALLBACKS

#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>
#include <TaskSchedulerDeclarations.h>
#include <time.h>

#include "config.h"
#include "ambientsensor.h"
#include "stemmasensor.h"

class PlantService : public Task {
public:
	bool Callback();

	void CheckSensors();
	void SaveToFile();
	void ReadFromFile();

	PlantService(Scheduler* scheduler);
	~PlantService() {};
private:
	AmbientSensor* ambient_sensor;
	StemmaSensor* soil_sensor;
};

#endif