#include "restserver.h"

RestServer::RestServer(AsyncWebServer *server) {
	timeClient = new NTPClient(ntpUDP);

	timeClient->begin();
	timeClient->setTimeOffset(ModuleConfig::timezone_offset);

	server->on("/module_info", HTTP_GET, [](AsyncWebServerRequest *request) {
		char json[500] = "";
		sprintf(json, "{\"moduleName\": \"%s\", \"ipAddress\": \"%s\"}", WiFi.macAddress().c_str(), WiFi.localIP().toString().c_str());
		request->send(200, "application/json", json);
	});

	server->on("/setup", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t *data, size_t len, size_t index, size_t total) {
		char raw_config[len] = "";
		strcpy(raw_config, (const char*)data);
		ModuleConfig::SetupModule(raw_config);
		request->send(201);
		delay(1000);
		ESP.restart();
	});
}