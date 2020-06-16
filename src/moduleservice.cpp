/*
 * File: moduleservice.cpp
 * Project: src
 * File Created: Tuesday, 24th March 2020 18:07:40
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday March 25th 2020 11:58:40
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "moduleservice.h"
void ModuleService::GetModuleInfo(char* info) {
	sprintf(info, "{\"moduleName\": \"%s\", \"ipAddress\": \"%s\", \"ambientTemperature\": \"%.1f\"}", WiFi.macAddress().c_str(), WiFi.localIP().toString().c_str(), 25.4);
}

ModuleService::ModuleService() {
	
}