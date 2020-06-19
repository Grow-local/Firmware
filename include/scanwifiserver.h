/*
 * File: scanwifiserver.h
 * Project: include
 * File Created: Wednesday, 20th November 2019 9:35:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday June 17th 2020 9:35:39
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef SCANWIFISERVER_H
#define SCANWIFISERVER_H

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
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