# Grow.local

[![Build Status](https://travis-ci.org/Grow-local/Firmware.svg?branch=master)](https://travis-ci.org/Grow-local/Firmware)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/29f0066291de41c09657aae728327c15)](https://www.codacy.com/gh/Grow-local/Firmware?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Grow-local/Firmware&amp;utm_campaign=Badge_Grade)

This is an open source plant care system for anyone. It utilizes low power, low cost WiFi enabled ESP32 microcontrollers to collect data and control equipment. A Raspberry Pi or alternative acts as a server for the individual plant-modules to connect to for configuration and management.

## Setting up for development

### Pre-requisites

VSCode and PlatformIO are required for development. Make sure you follow the setup instructions for PlatformIO.

I'm using an [ESP32 Feather from Adafruit](https://www.adafruit.com/product/3405) linked with a [simple temperature and humidity sensor](https://www.adafruit.com/product/3721) over i2c. This is all that is required for basic development. There is support for the [STEMMA soil sensor](https://www.adafruit.com/product/4026), but it is disabled at the moment.

### Configuration

When setting up a new ESP32 flash SPIFFS first, then flash the firmware. Afterwards you can flash either whenever. If you reflash SPIFFS, you will have to perform first time setup again.

Connect to the ESP by finding the network called `grow.local module`. Open a browser and navigate to `grow.local`, then wait 5 seconds before clicking the refresh button. Nearby 2.4ghz networks should appear, click the join button next to the one you would like to connect to, enter the password, and click join. The ESP will reboot, connect to the network, and set its mDNS name to `new-module`. From here setup continues in the app.

## WIP

This project is a Work in Progress. Much will change during development, and there are no guarantees that things will run perfectly. Help and feedback are appreciated.
