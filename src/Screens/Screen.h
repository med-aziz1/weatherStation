#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <WiFi.h>
#include <time.h>
#include <./DhtSensor/Values.h>
#include "./Config/Config.h"
/**
 * this class create the screens that will be displayed
 * in the oled class that herits from this class
 */

class Screens : public dhtSensor
{
public:
    void beginS();
    void end();
    void handle();
    void displayTemperature();
    void displayHumidity();
    void displayTime();
    void displayIndicator(uint8_t displayNumber);
    uint8_t displayScreenNum = 0;
};