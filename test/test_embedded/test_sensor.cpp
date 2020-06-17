/*
 * File: test_thing.cpp
 * Project: test_embedded
 * File Created: Tuesday, 16th June 2020 18:32:27
 * Author: Caroline (caroline@curieos.com)
 * -----
 * Last Modified: Tuesday June 16th 2020 19:57:33
 * Modified By: Caroline
 * -----
 * License: MIT License
 */

#include <Arduino.h>
#include <unity.h>

#include "plant/sensors/sensor.h"

class DummySensor : public Sensor {
public:
	DummySensor() : Sensor::Sensor("dummySensor") { }
	float ReadData() override {
		return 1.0;
	}

	std::vector<SensorData> GetData() {
		return this->data_history;
	}
};

void TestRecordData(void) {
	DummySensor dummy;
	struct tm time;
	dummy.RecordData(&time);
	auto data = dummy.GetData();
	TEST_ASSERT_EQUAL_FLOAT(1.0, data.front().value);
}

void RunTests() {
	RUN_TEST(TestRecordData);
}

void setup() {
	UNITY_BEGIN();
	RunTests();
	UNITY_END();
}

void loop() {
	
}
