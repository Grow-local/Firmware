/*
 * File: config.h
 * Project: include
 * File Created: Tuesday, 19th November 2019 17:04:12
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday June 17th 2020 10:15:43
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <TaskSchedulerDeclarations.h>
#include <time.h>
#include <vector>

const size_t CONFIG_MAX_FILE_SIZE = 2000;
const size_t JSON_CAPACITY = JSON_OBJECT_SIZE(2) + CONFIG_MAX_FILE_SIZE;

// Time Settings
#define TIME_SERVER "pool.ntp.org"
#define DAYLIGHT_SAVINGS_OFFSET 0 // 3600
#define TIMESTAMP_LENGTH 20

// Module Config Settings
#define MODULE_CONFIG_FILE_PATH "/module_config.json"

// Data Collection Settings
#define CHECK_SENSOR_PERIOD_MINUTES 10
#define DATA_MAX_AGE_HOURS 12

// Data Collection Math
#define CHECK_SENSOR_PERIOD (CHECK_SENSOR_PERIOD_MINUTES * TASK_MINUTE)
#define DATA_MAX_AGE (DATA_MAX_AGE_HOURS * TASK_HOUR)
#define DATA_MAX_SIZE (DATA_MAX_AGE / CHECK_SENSOR_PERIOD)

#define DEBUG
#ifdef DEBUG
#define BAUDRATE 115200
#endif

#define NETWORK_MAX_STRING_LENGTH 100
struct Network {
	char ssid[NETWORK_MAX_STRING_LENGTH];
	char password[NETWORK_MAX_STRING_LENGTH];
};

class ModuleConfig {
  public:
	static void ReadConfigFromFile();
	static void WriteConfigToFile();
	static void AddNetwork(const char *ssid, const char *password);
	static std::vector<Network> GetNetworks() { return networks; }
	static const char *GetName() { return name; }
	static int32_t GetTimezoneOffset() { return timezone_offset; }
	static void SetupModule(const char *raw_config);

  private:
	static char name[100];
	static int32_t timezone_offset;
	static std::vector<Network> networks;
};

class PlantConfig {
  public:
	static const char *GetName() { return name; }
	static void SetupPlant(const char *raw_config);

  private:
	static char name[100];
};

#endif
