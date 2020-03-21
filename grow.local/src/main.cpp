#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>
#include <vector>
#include <elapsedMillis.h>

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

	if (ModuleConfig::networks.size() > 0) {
		int network = 0;
		while (WiFi.status() != WL_CONNECTED && network < ModuleConfig::networks.size()) {
			WiFi.begin(ModuleConfig::networks[network].ssid, ModuleConfig::networks[network].password);

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
			restServer = new RestServer(Server);

			Server->begin();

			MDNS.begin(ModuleConfig::name);
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

void loop() {}
