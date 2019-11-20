#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>

#include "config.h"
#include "scanwifiserver.h"
#include "restserver.h"

AsyncWebServer* Server = new AsyncWebServer(80);

ScanWifiServer* scanWifi;
RestServer* restServer;

void setup() {
	#ifdef DEBUG
	Serial.begin(BAUDRATE);
	#endif

	WiFi.mode(WIFI_AP_STA);
	SPIFFS.begin();

	scanWifi = new ScanWifiServer(Server);
	
	Server->begin();

	MDNS.begin("grow");
	MDNS.addService("http", "tcp", 80);
}

void loop() {}
