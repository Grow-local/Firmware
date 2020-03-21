/*
 * File: config.cpp
 * Project: src
 * File Created: Friday, 20th March 2020 10:56:27
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Saturday March 21st 2020 9:40:11
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "config.h"

const char* MODULE_CONFIG_FILE_PATH = "/module_config.json";

char ModuleConfig::name[100] = "";
int16_t ModuleConfig::timezone_offset = 0;

void ModuleConfig::ReadConfigFromFile() {
	File file = SPIFFS.open(MODULE_CONFIG_FILE_PATH);
	if (!file) {
#ifdef DEBUG
		Serial.println("Failed to open module config file for reading");
#endif
		return;
	}

	DynamicJsonDocument json_config(JSON_CAPACITY);
	auto raw_config = file.readString();
	deserializeJson(json_config, raw_config);
	try { strcpy(name, json_config["moduleName"]); }
	catch(int e) { strcpy(name, ""); }
	timezone_offset = json_config["timezoneOffset"];
	
	file.close();
}

void ModuleConfig::WriteConfigToFile() {
	File file = SPIFFS.open(MODULE_CONFIG_FILE_PATH, FILE_WRITE);
	if (!file) {
#ifdef DEBUG
		Serial.println("Failed to open module config file for writing");
#endif
		return;
	}

	char config_str[CONFIG_MAX_FILE_SIZE] = "";
	sprintf(config_str, "{ moduleName: \"%s\", timezoneOffset: \"%d\" }", name, timezone_offset);
	file.print(config_str);

	file.close();
}

void ModuleConfig::SetupModule(const char *raw_config) {
	DynamicJsonDocument json_config(JSON_CAPACITY);
	deserializeJson(json_config, raw_config);
	timezone_offset = json_config["timezoneOffset"];
	timezone_offset *= 60;
	strcpy(name, json_config["name"]);
	Serial.println(timezone_offset);
	Serial.println(name);
	ModuleConfig::WriteConfigToFile();
}