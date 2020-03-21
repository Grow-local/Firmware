/**
 * @Author: curieos
 * @Date:   2019-06-19T19:14:29-05:00
 * @Email:  caroline@curieos
 * @Filename: config.h
 * @Last modified by:   curieos
 * @Last modified time: 2019-06-19T19:17:29-05:00
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>

const size_t CONFIG_MAX_FILE_SIZE = 1000;
const size_t JSON_CAPACITY = JSON_OBJECT_SIZE(2) + CONFIG_MAX_FILE_SIZE;

#define DEBUG
#ifdef DEBUG
	#define BAUDRATE 115200
#endif

#endif
