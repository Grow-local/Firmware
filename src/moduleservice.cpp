/*
 * File: moduleservice.cpp
 * Project: src
 * File Created: Tuesday, 24th March 2020 18:07:40
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Friday June 19th 2020 14:56:44
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "moduleservice.h"
void ModuleService::GetModuleInfo(char* info) {
	sprintf(info, "{\"moduleName\": \"%s\", \"ipAddress\": \"%s\", \"version\": \"%s\"}", WiFi.macAddress().c_str(), WiFi.localIP().toString().c_str(), VERSION);
}

ModuleService::ModuleService() {
	
}