/*
 * File: ambientsensor.cpp
 * Project: src
 * File Created: Thursday, 26th March 2020 9:21:17
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Thursday March 26th 2020 10:10:25
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "ambientsensor.h"

void AmbientSensor::RecordData(const char* timestamp) {
	struct SensorData humidity;
	struct SensorData temperature;
	strcpy(humidity.timestamp, timestamp);
	strcpy(temperature.timestamp, timestamp);
	do {
		temperature.value = this->readTemperature();
	} while (isnan(temperature.value));
	do {
		humidity.value = this->readHumidity();
	} while (isnan(humidity.value));
	temperature_history.push_back(temperature);
	if (temperature_history.size() > 54) temperature_history.erase(temperature_history.begin());
	humidity_history.push_back(humidity);
	if (humidity_history.size() > 54) humidity_history.erase(humidity_history.begin());
}

void AmbientSensor::DataToJSONArray(char* json) {
	char temperature_history_string[1600] = "\"t\":[";
	char humidity_history_string[1600] = "\"h\":[";
	for (auto temperature : temperature_history) {
		char temperature_string[28] = "";
		snprintf(temperature_string, 28, "{\"v\":\"%.1f\",\"t\":\"%s\"}", temperature.value, temperature.timestamp);
		strcat(temperature_history_string, temperature_string);
		if (strcmp(temperature.timestamp, temperature_history.back().timestamp)) strcat(temperature_history_string, ",");
	}
	for (auto humidity : humidity_history) {
		char humidity_string[28] = "";
		snprintf(humidity_string, 28, "{\"v\":\"%.1f\",\"t\":\"%s\"}", humidity.value, humidity.timestamp);
		strcat(humidity_history_string, humidity_string);
		if (strcmp(humidity.timestamp, humidity_history.back().timestamp)) strcat(humidity_history_string, ",");
	}
	strcat(temperature_history_string, "]");
	strcat(humidity_history_string, "]");
	snprintf(json, 3200, "%s, %s", temperature_history_string, humidity_history_string);
}