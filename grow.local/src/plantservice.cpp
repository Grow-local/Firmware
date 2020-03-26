/*
 * File: plantservice.cpp
 * Project: src
 * File Created: Tuesday, 24th March 2020 18:29:29
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Thursday March 26th 2020 10:14:34
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
	struct tm timeinfo;
	char timestamp[TIMESTAMP_LENGTH] = "";
	getLocalTime(&timeinfo);
	strftime(timestamp, TIMESTAMP_LENGTH, "%H:%M:%S", &timeinfo);
	Serial.printf("Reading plant sensors at %2.d:%02d:%02d...\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
	this->ambient_sensor->RecordData(timestamp);
}

void PlantService::GetPlantInfo(char* info) {
	char ambient_history_string[3200] = "";
	this->ambient_sensor->DataToJSONArray(ambient_history_string);
	snprintf(info, 5000, "{%s}", ambient_history_string);
}

PlantService::PlantService(Scheduler* scheduler) : Task(10*TASK_MINUTE, TASK_FOREVER, scheduler, true) {
	this->ambient_sensor = new AmbientSensor();

	this->ambient_sensor->begin();
}