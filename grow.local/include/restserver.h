#ifndef RESTSERVER_H
#define RESTSERVER_H

#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "config.h"

class RestServer {
public:
	RestServer(AsyncWebServer *server);
	~RestServer();
private:
	WiFiUDP ntpUDP;
	NTPClient *timeClient;
};

#endif