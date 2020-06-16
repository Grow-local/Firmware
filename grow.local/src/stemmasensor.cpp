/*
 * File: stemma_sensor.cpp
 * Project: src
 * File Created: Wednesday, 8th April 2020 12:35:11
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Monday June 15th 2020 22:05:32
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "stemmasensor.h"

StemmaSensor::StemmaSensor() {
	this->begin(0x36);
}

void StemmaSensor::RecordData(struct tm* timestamp) {
	struct SensorData moisture;
	strftime(moisture.timestamp, TIMESTAMP_LENGTH, "%FT%T", timestamp);
	do {
		moisture.value = this->touchRead(0);
	} while (isnan(moisture.value));
	moisture_history.push_back(moisture);
	if (moisture_history.size() > DATA_MAX_SIZE) moisture_history.erase(moisture_history.begin());
}

void StemmaSensor::SaveToFile(File* file) {
	file->print(",\"soilMoisture\":[");
	for (auto moisture : moisture_history) {
		file->printf("{\"value\":%.1f,\"time\":\"%s\"}", moisture.value, moisture.timestamp);
		if (strcmp(moisture.timestamp, moisture_history.back().timestamp)) file->print(",");
	}
	file->print("]");
}

void StemmaSensor::ReadFromFile(File* file) {
	DynamicJsonDocument json(20000);	
	deserializeJson(json, *file);
	JsonArray moisture_data = json["soilMoisture"];
	for (auto moisture_point : moisture_data) {
		struct SensorData data_point;
		data_point.value = moisture_point["value"];
		strcpy(data_point.timestamp, moisture_point["time"]);
		moisture_history.push_back(data_point);
	}
}