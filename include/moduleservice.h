/*
 * File: moduleservice.h
 * Project: include
 * File Created: Tuesday, 24th March 2020 18:05:04
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Wednesday June 17th 2020 9:35:24
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#ifndef MODULESERVICE_H
#define MODULESERVICE_H

#define _TASK_TIMEOUT
#define _TASK_OO_CALLBACKS

#include <WiFi.h>

#include "config.h"

class ModuleService {
   public:
    void GetModuleInfo(char *info);

    ModuleService();
    ~ModuleService();

   private:
};

#endif