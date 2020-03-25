/*
 * File: plantservice.h
 * Project: include
 * File Created: Tuesday, 24th March 2020 18:20:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday March 25th 2020 11:40:37
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

#include "config.h"

class PlantService : public Task {
public:
	bool Callback();

	void CheckSensors();
	void GetPlantInfo(char* info);

	PlantService(Scheduler* scheduler);
	~PlantService() {};
private:
	Adafruit_AM2320* am2320;
	float temperature;
	float humidity;
};

#endif