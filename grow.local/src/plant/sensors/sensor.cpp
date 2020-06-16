/*
 * File: sensor.cpp
 * Project: src
 * File Created: Monday, 15th June 2020 23:36:44
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Tuesday June 16th 2020 10:21:13
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "plant/sensors/sensor.h"

Sensor::Sensor(const char* label) {
	this->label = label;
}

void Sensor::RecordData(struct tm* timestamp) {
	struct SensorData data;
	strftime(data.timestamp, TIMESTAMP_LENGTH, "%FT%T", timestamp);
	do {
		data.value = this->ReadData();
	} while (isnan(data.value));
	data_history.push_back(data);
	if (data_history.size() > DATA_MAX_SIZE) data_history.erase(data_history.begin());
}

void Sensor::SaveToFile(File* file) {
	file->printf("\"%s\":[", label);
	for (auto data : data_history) {
		file->printf("{\"value\":%.1f,\"time\":\"%s\"}", data.value, data.timestamp);
		if (strcmp(data.timestamp, data_history.back().timestamp)) file->print(",");
	}
	file->print("]");
}

void Sensor::ReadFromFile(File* file) {
	DynamicJsonDocument json(20000);	
	deserializeJson(json, *file);
	JsonArray json_data = json[this->label];
	for (auto json_point : json_data) {
		struct SensorData data_point;
		data_point.value = json_point["value"];
		strcpy(data_point.timestamp, json_point["time"]);
		this->data_history.push_back(data_point);
	}
}