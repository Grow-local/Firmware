/*
 * File: plantservice.cpp
 * Project: src
 * File Created: Tuesday, 24th March 2020 18:29:29
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Monday June 15th 2020 22:31:18
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "plantservice.h"

bool PlantService::Callback() {
	CheckSensors();
	SaveToFile();
	return true;
}

void PlantService::CheckSensors() {
	struct tm timeinfo;
	getLocalTime(&timeinfo);
#ifdef DEBUG
	Serial.println(&timeinfo, "Reading plant sensors at %FT%T...");
#endif
	this->ambient_sensor->RecordData(&timeinfo);
	//this->soil_sensor->RecordData(&timeinfo);
}

void PlantService::SaveToFile() {
	File file = SPIFFS.open("/data.json", FILE_WRITE);
	if (!file) {
#ifdef DEBUG
		Serial.println("Failed to open data file for writing");
#endif
		return;
	}
	file.print("{");
	this->ambient_sensor->SaveToFile(&file);
	//this->soil_sensor->SaveToFile(&file);
	file.print("}");
	file.close();
}

void PlantService::ReadFromFile() {
	File file = SPIFFS.open("/data.json", "r");
	if (!file) {
#ifdef DEBUG
		Serial.println("Failed to open data file for reading");
#endif
		return;
	}
	this->ambient_sensor->ReadFromFile(&file);
	//this->soil_sensor->ReadFromFile(&file);
	file.close();
}

PlantService::PlantService(Scheduler* scheduler) : Task(CHECK_SENSOR_PERIOD, TASK_FOREVER, scheduler, true) {
	this->ambient_sensor = new AmbientSensor();
	//this->soil_sensor = new StemmaSensor();

	this->ambient_sensor->begin();

	ReadFromFile();
}