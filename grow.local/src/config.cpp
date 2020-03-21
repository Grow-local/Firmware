/*
 * File: config.cpp
 * Project: src
 * File Created: Friday, 20th March 2020 10:56:27
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Saturday March 21st 2020 9:35:40
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "config.h"

const char* MODULE_CONFIG_FILE_PATH = "/module_config.json";

char ModuleConfig::name[100] = "";
int16_t ModuleConfig::timezone_offset = 0;

void ModuleConfig::SetupModule(const char *raw_config) {
	DynamicJsonDocument json_config(JSON_CAPACITY);
	deserializeJson(json_config, raw_config);
	timezone_offset = json_config["timezoneOffset"];
	timezone_offset *= 60;
	strcpy(name, json_config["name"]);
	Serial.println(timezone_offset);
	Serial.println(name);
}