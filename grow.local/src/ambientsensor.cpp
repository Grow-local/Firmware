/*
 * File: ambientsensor.cpp
 * Project: src
 * File Created: Thursday, 26th March 2020 9:21:17
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Monday June 15th 2020 22:30:45
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "ambientsensor.h"

void AmbientSensor::RecordData(struct tm* timestamp) {
	struct SensorData humidity;
	struct SensorData temperature;
	strftime(temperature.timestamp, TIMESTAMP_LENGTH, "%FT%T", timestamp);
	strftime(humidity.timestamp, TIMESTAMP_LENGTH, "%FT%T", timestamp);
	do {
		temperature.value = this->readTemperature();
	} while (isnan(temperature.value));
	do {
		humidity.value = this->readHumidity();
	} while (isnan(humidity.value));
	temperature_history.push_back(temperature);
	if (temperature_history.size() > DATA_MAX_SIZE) temperature_history.erase(temperature_history.begin());
	humidity_history.push_back(humidity);
	if (humidity_history.size() > DATA_MAX_SIZE) humidity_history.erase(humidity_history.begin());
}

void AmbientSensor::SaveToFile(File* file) {
	file->print("\"ambientTemperature\":[");
	for (auto temperature : temperature_history) {
		file->printf("{\"value\":%.1f,\"time\":\"%s\"}", temperature.value, temperature.timestamp);
		if (strcmp(temperature.timestamp, temperature_history.back().timestamp)) file->print(",");
	}
	file->print("],\"humidity\":[");
	for (auto humidity : humidity_history) {
		file->printf("{\"value\":%.1f,\"time\":\"%s\"}", humidity.value, humidity.timestamp);
		if (strcmp(humidity.timestamp, humidity_history.back().timestamp)) file->print(",");
	}
	file->print("]");
}

void AmbientSensor::ReadFromFile(File* file) {
	DynamicJsonDocument json(20000);	
	deserializeJson(json, *file);
	JsonArray temperature_data = json["ambientTemperature"];
	JsonArray humidity_data = json["humidity"];
	for (auto temperature_point : temperature_data) {
		struct SensorData data_point;
		data_point.value = temperature_point["value"];
		strcpy(data_point.timestamp, temperature_point["time"]);
		temperature_history.push_back(data_point);
	}
	for (auto humidity_point : humidity_data) {
		struct SensorData data_point;
		data_point.value = humidity_point["value"];
		strcpy(data_point.timestamp, humidity_point["time"]);
		humidity_history.push_back(data_point);
	}
}