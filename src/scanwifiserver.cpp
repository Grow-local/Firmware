/*
 * File: scanwifiserver.cpp
 * Project: src
 * File Created: Wednesday, 20th November 2019 9:35:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Thursday March 26th 2020 20:43:25
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include "scanwifiserver.h"

ScanWifiServer::ScanWifiServer(AsyncWebServer *server) {
    WiFi.softAP("grow.local module");

    server->serveStatic("/", SPIFFS, "/www/")
	.setCacheControl("max-age=600")
	.setDefaultFile("index.html");

    server->on("/scan", HTTP_GET, [](AsyncWebServerRequest *request) {
	String json = "[";
	int n = WiFi.scanComplete();
	if (n == -2) {
	    WiFi.scanNetworks(true);
	} else if (n) {
	    for (int i = 0; i < n; ++i) {
		if (i) json += ",";
		json += "{";
		json += "\"rssi\":" + String(WiFi.RSSI(i));
		json += ",\"ssid\":\"" + WiFi.SSID(i) + "\"";
		json += ",\"bssid\":\"" + WiFi.BSSIDstr(i) + "\"";
		json += ",\"channel\":" + String(WiFi.channel(i));
		json += ",\"secure\":" + String(WiFi.encryptionType(i));
		json += "}";
	    }
	    WiFi.scanDelete();
	    if (WiFi.scanComplete() == -2) {
		WiFi.scanNetworks(true);
	    }
	}
	json += "]";
	request->send(200, "application/json", json);
	json = String();
    });

    server->on(
	"/join", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL,
	[](AsyncWebServerRequest *request, uint8_t *data, size_t len,
           size_t index, size_t total) {
	    char network[len] = "";
	    strcat(network, (const char *)data);
	    DynamicJsonDocument json_network(JSON_CAPACITY);
	    deserializeJson(json_network, network);
	    ModuleConfig::AddNetwork(json_network["ssid"],
	                             json_network["password"]);
	    request->send(201);
	    delay(1000);
	    ESP.restart();
	});
}