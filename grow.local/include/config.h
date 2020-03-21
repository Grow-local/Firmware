/*
 * File: config.h
 * Project: include
 * File Created: Tuesday, 19th November 2019 17:04:12
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Saturday March 21st 2020 9:34:15
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <SPIFFS.h>

const size_t CONFIG_MAX_FILE_SIZE = 1000;
const size_t JSON_CAPACITY = JSON_OBJECT_SIZE(2) + CONFIG_MAX_FILE_SIZE;

#define DEBUG
#ifdef DEBUG
	#define BAUDRATE 115200
#endif

class ModuleConfig {
public:
	static char name[100];
	static int16_t timezone_offset;
	static void SetupModule(const char* raw_config);
};

class PlantConfig {
public:
	static char name[100];
};

#endif
