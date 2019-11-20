#ifndef SCANWIFISERVER_H
#define SCANWIFISERVER_H

#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>

class ScanWifiServer {
public:
	ScanWifiServer(AsyncWebServer *server);
	~ScanWifiServer();
private:

};

#endif