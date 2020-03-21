#ifndef SCANWIFISERVER_H
#define SCANWIFISERVER_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>

#include "config.h"

class ScanWifiServer {
public:
	ScanWifiServer(AsyncWebServer *server);
	~ScanWifiServer();
private:
	
};

#endif