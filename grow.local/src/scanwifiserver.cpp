#include "scanwifiserver.h"

ScanWifiServer::ScanWifiServer(AsyncWebServer *server) {
	WiFi.softAP("grow.local module");

	server->serveStatic("/", SPIFFS, "/");

	server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		File file = SPIFFS.open("/index.html", "r");
		AsyncWebServerResponse *response =
			request->beginResponse(200, "text/html", file.readStringUntil(EOF));
		response->addHeader("Connection", "close");
		request->send(response);
	});

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

	server->on("/join", HTTP_POST, [](AsyncWebServerRequest *request) {
		
	});
}