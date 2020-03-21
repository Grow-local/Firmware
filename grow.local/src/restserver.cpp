/*
 * File: restserver.cpp
 * Project: src
 * File Created: Wednesday, 20th November 2019 9:35:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Saturday March 21st 2020 14:16:23
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "restserver.h"

RestServer::RestServer(AsyncWebServer *server) {
	timeClient = new NTPClient(ntpUDP);

	timeClient->begin();
	timeClient->setTimeOffset(ModuleConfig::timezone_offset);

	server->on("/module/info", HTTP_GET, [](AsyncWebServerRequest *request) {
		char json[500] = "";
		sprintf(json, "{\"moduleName\": \"%s\", \"ipAddress\": \"%s\"}", WiFi.macAddress().c_str(), WiFi.localIP().toString().c_str());
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
}