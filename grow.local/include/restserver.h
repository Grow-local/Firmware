/*
 * File: restserver.h
 * Project: include
 * File Created: Wednesday, 20th November 2019 9:35:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Saturday March 21st 2020 14:16:03
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

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