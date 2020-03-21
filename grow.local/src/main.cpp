/*
 * File: main.cpp
 * Project: src
 * File Created: Tuesday, 19th November 2019 17:04:12
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Saturday March 21st 2020 14:54:32
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef UNIT_TEST

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>
#include <vector>
#include <ArduinoOTA.h>

#include "config.h"
#include "restserver.h"
#include "scanwifiserver.h"

AsyncWebServer *Server = new AsyncWebServer(80);

ScanWifiServer *scanWifi;
RestServer *restServer;

void setup() {
#ifdef DEBUG
	Serial.begin(BAUDRATE);
	delay(2000);
#endif

	SPIFFS.begin();
	ModuleConfig::ReadConfigFromFile();

	auto networks = ModuleConfig::GetNetworks();
	if (networks.size() > 0) {
		int network = 0;
		while (WiFi.status() != WL_CONNECTED && network < networks.size()) {
			WiFi.begin(networks[network].ssid, networks[network].password);

			while (WiFi.status() != WL_CONNECTED) {
				if (WiFi.status() == WL_CONNECT_FAILED ||
					WiFi.status() == WL_NO_SSID_AVAIL)
					break;
			}
			network++;
		}
		if (WiFi.status() == WL_CONNECTED) {
#ifdef DEBUG
			Serial.println("Connected");
#endif

			ArduinoOTA.onStart([]() {
				char type[100] = "";
				if (ArduinoOTA.getCommand() == U_FLASH) strcat(type, "sketch");
				else {
					strcat(type, "filesystem");
					SPIFFS.end();
				}
#ifdef DEBUG
				Serial.printf("Updating %s\n", type);
#endif
			}).onEnd([]() {
#ifdef DEBUG
				Serial.println("\nEnd");
#endif
			}).onProgress([](unsigned int progress, unsigned int total) {
#ifdef DEBUG
				Serial.printf("Progress: %u%%\n", (progress / (total / 100)));
#endif
			}).onError([](ota_error_t error) {

			});

			ArduinoOTA.begin();

			restServer = new RestServer(Server);

			Server->begin();

			MDNS.begin(ModuleConfig::GetName());
			MDNS.addService("http", "tcp", 80);
		} else WiFi.mode(WIFI_AP);
	} else WiFi.mode(WIFI_AP);

	if (WiFi.getMode() == WIFI_AP) {
#ifdef DEBUG
		Serial.println("Starting ScanWifiServer");
#endif

		scanWifi = new ScanWifiServer(Server);

		Server->begin();

		MDNS.begin("grow");
		MDNS.addService("http", "tcp", 80);
	}
}

void loop() {
	if (WiFi.getMode() != WIFI_AP) ArduinoOTA.handle();
}

#endif
