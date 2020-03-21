/*
 * File: config.h
 * Project: include
 * File Created: Tuesday, 19th November 2019 17:04:12
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Saturday March 21st 2020 13:29:53
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <vector>

const size_t CONFIG_MAX_FILE_SIZE = 1000;
const size_t JSON_CAPACITY = JSON_OBJECT_SIZE(2) + CONFIG_MAX_FILE_SIZE;

#define DEBUG
#ifdef DEBUG
	#define BAUDRATE 115200
#endif

struct Network {
	char ssid[100];
	char password[100];
};

class ModuleConfig {
public:
	static char name[100];
	static int16_t timezone_offset;
	static std::vector<Network> networks;

	static void ReadConfigFromFile();
	static void WriteConfigToFile();
	static void AddNetwork(const char* ssid, const char* password);
	static void SetupModule(const char* raw_config);
private:
};

class PlantConfig {
public:
	static char name[100];
};

#endif
