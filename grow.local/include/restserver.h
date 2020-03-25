/*
 * File: restserver.h
 * Project: include
 * File Created: Wednesday, 20th November 2019 9:35:52
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday March 25th 2020 12:42:10
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef RESTSERVER_H
#define RESTSERVER_H

#define _TASK_TIMEOUT
#define _TASK_OO_CALLBACKS

#include <ESPAsyncWebServer.h>
#include <TaskScheduler.h>

#include "config.h"
#include "moduleservice.h"
#include "plantservice.h"

class RestServer {
public:
	ModuleService* GetModuleService() { return module_service; }
	PlantService* GetPlantService() { return plant_service; }
	
	RestServer(AsyncWebServer *server);
	~RestServer();
private:
	Scheduler *scheduler;
	ModuleService *module_service;
	PlantService *plant_service;
};

#endif