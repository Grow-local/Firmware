/*
 * File: plantservice.h
 * Project: include
 * File Created: Tuesday, 24th March 2020 18:20:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday June 17th 2020 10:12:12
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef PLANT_PLANT_SERVICE_H
#define PLANT_PLANT_SERVICE_H

#define _TASK_TIMEOUT
#define _TASK_OO_CALLBACKS

#include <Adafruit_AM2320.h>
#include <Adafruit_Sensor.h>
#include <TaskSchedulerDeclarations.h>
#include <time.h>

#include "config.h"
#include "plant/sensors/ambient_humidity_sensor.h"
#include "plant/sensors/ambient_temperature_sensor.h"
#include "plant/sensors/stemma_sensor.h"

class PlantService : public Task {
  public:
	bool Callback();

	void CheckSensors();
	void SaveToFile();
	void ReadFromFile();

	PlantService(Scheduler *scheduler);
	~PlantService(){};

  private:
	AmbientTemperatureSensor *ambient_temperature_sensor;
	AmbientHumiditySensor *ambient_humidity_sensor;
};

#endif