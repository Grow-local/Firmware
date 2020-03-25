/*
 * File: restserver.cpp
 * Project: src
 * File Created: Wednesday, 20th November 2019 9:35:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday March 25th 2020 11:58:45
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "restserver.h"

RestServer::RestServer(AsyncWebServer *server) {
	scheduler = new Scheduler();

	module_service = new ModuleService();
	plant_service = new PlantService(scheduler);
	
	server->on("/module/info", HTTP_GET, [this](AsyncWebServerRequest *request) {
		char json[1000] = "";
		this->GetModuleService()->GetModuleInfo(json);
		request->send(200, "application/json", json);
	});

	server->on("/module/setup", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t *data, size_t len, size_t index, size_t total) {
		char raw_config[len] = "";
		strcpy(raw_config, (const char*)data);
		ModuleConfig::SetupModule(raw_config);
		request->send(201);
		delay(1000);
		ESP.restart();
	});

	server->on("/plant/info", HTTP_GET, [this](AsyncWebServerRequest *request) {
		char json[1000] = "";
		this->GetPlantService()->GetPlantInfo(json);
		request->send(200, "application/json", json);
	}); 
}