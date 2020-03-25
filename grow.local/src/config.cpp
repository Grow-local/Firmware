/*
 * File: config.cpp
 * Project: src
 * File Created: Friday, 20th March 2020 10:56:27
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Tuesday March 24th 2020 15:33:49
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "config.h"

char ModuleConfig::name[100] = "";
int32_t ModuleConfig::timezone_offset = 0;
std::vector<Network> ModuleConfig::networks = {};

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

	JsonArray networks_json = json_config["networks"];
	for(auto network : networks_json) {
		struct Network newNetwork;
		try {
			strcpy(newNetwork.ssid, network["ssid"]);
			strcpy(newNetwork.password, network["password"]);
		} catch(int e) { break; }
		networks.push_back(newNetwork);
	}
	
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

	char networks_string[1000] = "[";
	for (std::vector<Network>::iterator iter = networks.begin(); iter < networks.end(); iter++) {
		char network_string[200] = "";
		sprintf(network_string, "{\"ssid\": \"%s\", \"password\": \"%s\"}", iter->ssid, iter->password);
		strcat(networks_string, network_string);
		if (iter != networks.end()) strcat(network_string, ",");
	}

	char config_str[CONFIG_MAX_FILE_SIZE] = "";
	sprintf(config_str, "{\"moduleName\": \"%s\", \"timezoneOffset\": \"%d\", \"networks\": %s}", name, timezone_offset, networks_string);
	file.print(config_str);

	file.close();
}

void ModuleConfig::AddNetwork(const char* ssid, const char* password) {
	struct Network newNetwork;
	strcpy(newNetwork.ssid, ssid);
	strcpy(newNetwork.password, password);
	networks.push_back(newNetwork);
	ModuleConfig::WriteConfigToFile();
}

void ModuleConfig::SetupModule(const char *raw_config) {
	DynamicJsonDocument json_config(JSON_CAPACITY);
	deserializeJson(json_config, raw_config);
	timezone_offset = json_config["timezoneOffset"];
	timezone_offset *= 3600;
	strcpy(name, json_config["name"]);
	ModuleConfig::WriteConfigToFile();
}