/*
 * File: plantservice.cpp
 * Project: src
 * File Created: Tuesday, 24th March 2020 18:29:29
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday March 25th 2020 11:33:57
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "plantservice.h"

bool PlantService::Callback() {
	CheckSensors();
	return true;
}

void PlantService::CheckSensors() {
	do {
		temperature = am2320->readTemperature();
	} while (isnan(temperature));
}

void PlantService::GetPlantInfo(char* info) {
	sprintf(info, "{\"ambientTemperature\": \"%.1f\", \"humidity\": \"%.1f\"}", temperature, humidity);
}

PlantService::PlantService(Scheduler* scheduler) : Task(10*TASK_MINUTE, TASK_FOREVER, scheduler, true) {
	this->am2320 = new Adafruit_AM2320();
	this->temperature = 0;
	this->humidity = 0;

	this->am2320->begin();
}