#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

#include "scanwifiserver.h"
#include "restserver.h"

AsyncWebServer Server(80);
IPAddress apIP(192, 168, 4, 1);

ScanWifiServer* scanWifi;
RestServer* restServer;

void setup() {
	WiFi.mode(WIFI_AP_STA);
    WiFi.softAP("grow.local module");

	Server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		AsyncWebServerResponse *response =
			request->beginResponse(200, "application/json", "{}");
		response->addHeader("Connection", "close");
		request->send(response);
	});

	Server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request) {
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

	Server.begin();

	MDNS.begin("grow");
	MDNS.addService("http", "tcp", 80);
}

void loop() {}
