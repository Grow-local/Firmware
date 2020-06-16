/*
 * File: test_main.cpp
 * Project: test
 * File Created: Saturday, 21st March 2020 11:09:42
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Saturday March 21st 2020 12:43:38
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include <Arduino.h>
#include <unity.h>

#include "config.h"

#define MODULE_NAME "name"

void TestModuleNameEmpty(void) {
	TEST_ASSERT_EQUAL_STRING(ModuleConfig::name, "");
}

void TestModuleName(void) {
	TEST_ASSERT_EQUAL_STRING(ModuleConfig::name, MODULE_NAME);
}

void TestTimezoneOffset(void) {
	TEST_ASSERT_EQUAL_INT16(ModuleConfig::timezone_offset, 0);
}

void setup() {
	UNITY_BEGIN();
}

void loop() {
	RUN_TEST(TestModuleNameEmpty);
	strcat(ModuleConfig::name, MODULE_NAME);
	RUN_TEST(TestModuleName);
	
	RUN_TEST(TestTimezoneOffset);

	

	UNITY_END();
}