#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>

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

void setup() {
#ifdef DEBUG
	Serial.begin(BAUDRATE);
	delay(2000);
#endif

	WiFi.mode(WIFI_AP_STA);
	SPIFFS.begin();

	scanWifi = new ScanWifiServer(Server);
	
	Server->begin();

	MDNS.begin("grow");
	MDNS.addService("http", "tcp", 80);
}

void loop() {}
