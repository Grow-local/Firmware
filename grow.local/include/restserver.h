/*
 * File: restserver.h
 * Project: include
 * File Created: Wednesday, 20th November 2019 9:35:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Tuesday June 16th 2020 0:01:05
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef RESTSERVER_H
#define RESTSERVER_H

#define _TASK_TIMEOUT
#define _TASK_OO_CALLBACKS

#include <ESPAsyncWebServer.h>
#include <TaskSchedulerDeclarations.h>
#include <SPIFFS.h>

#include "config.h"
#include "moduleservice.h"
#include "plant/plant_service.h"

class RestServer {
public:
	ModuleService* GetModuleService() { return module_service; }
	PlantService* GetPlantService() { return plant_service; }
	
	RestServer(AsyncWebServer *server, Scheduler *scheduler);
	~RestServer();
private:
	Scheduler *scheduler;
	ModuleService *module_service;
	PlantService *plant_service;
};

#endif