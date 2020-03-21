#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>
#include <vector>

#include "config.h"
#include "restserver.h"
#include "scanwifiserver.h"

AsyncWebServer *Server = new AsyncWebServer(80);

ScanWifiServer *scanWifi;
RestServer *restServer;

struct Network {
	char ssid[100];
	char password[100];
};

std::vector<Network> readAP(fs::FS &fs) {
	// fs.remove("/ap.txt");
	File file = fs.open("/ap.txt");
	std::vector<Network> networks;
	if (!file) {
#ifdef DEBUG
		Serial.println("Failed to open file for reading");
#endif
		return networks;
	}

	while (file.available()) {
		DynamicJsonDocument n(JSON_CAPACITY);
		auto s = file.readStringUntil('\n');
		deserializeJson(n, s);
		struct Network network;
		strcpy(network.ssid, n["ssid"]);
		strcpy(network.password, n["password"]);
		networks.push_back(network);
	}

	file.close();
	return networks;
}

void setup() {
#ifdef DEBUG
	Serial.begin(BAUDRATE);
	delay(2000);
#endif

	SPIFFS.begin();

	auto networks = readAP(SPIFFS);
	if (networks.size() == 0) {
#ifdef DEBUG
		Serial.println("Starting ScanWifiServer");
#endif
		WiFi.mode(WIFI_AP);

		scanWifi = new ScanWifiServer(Server);

		Server->begin();

		MDNS.begin("grow");
		MDNS.addService("http", "tcp", 80);
	}
}

void loop() {}
