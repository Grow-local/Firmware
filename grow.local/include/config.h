/*
 * File: config.h
 * Project: include
 * File Created: Tuesday, 19th November 2019 17:04:12
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Thursday March 26th 2020 10:14:11
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <vector>
#include <time.h>

const size_t CONFIG_MAX_FILE_SIZE = 2000;
const size_t JSON_CAPACITY = JSON_OBJECT_SIZE(2) + CONFIG_MAX_FILE_SIZE;


// Time Settings
#define TIME_SERVER "pool.ntp.org"
#define DAYLIGHT_SAVINGS_OFFSET 3600
#define TIMESTAMP_LENGTH 9

// Module Config Settings
#define MODULE_CONFIG_FILE_PATH "/module_config.json"


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
	static void ReadConfigFromFile();
	static void WriteConfigToFile();
	static void AddNetwork(const char* ssid, const char* password);
	static std::vector<Network> GetNetworks() { return networks; }
	static const char* GetName() { return name; }
	static int32_t GetTimezoneOffset() { return timezone_offset; }
	static void SetupModule(const char* raw_config);
private:
	static char name[100];
	static int32_t timezone_offset;
	static std::vector<Network> networks;
};

class PlantConfig {
public:
	static char name[100];
};

#endif
