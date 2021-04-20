/*
 * File: plantservice.cpp
 * Project: src
 * File Created: Tuesday, 24th March 2020 18:29:29
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Thursday June 18th 2020 14:55:55
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "plant/plant_service.h"

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
    this->ambient_temperature_sensor->RecordData(&timeinfo);
    this->ambient_humidity_sensor->RecordData(&timeinfo);
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
    this->ambient_temperature_sensor->SaveToFile(&file);
    file.print(",");
    this->ambient_humidity_sensor->SaveToFile(&file);
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

    DynamicJsonDocument json(20000);
    deserializeJson(json, file);

    this->ambient_temperature_sensor->ReadFromJSON(&json);
    this->ambient_humidity_sensor->ReadFromJSON(&json);
    file.close();
}

PlantService::PlantService(Scheduler *scheduler)
    : Task(CHECK_SENSOR_PERIOD, TASK_FOREVER, scheduler, true) {
    this->ambient_temperature_sensor = new AmbientTemperatureSensor();
    this->ambient_humidity_sensor = new AmbientHumiditySensor();

    this->ambient_temperature_sensor->begin();
    this->ambient_humidity_sensor->begin();

    ReadFromFile();
}