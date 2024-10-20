#pragma once
#include <DHTesp.h>
#include"./Config/Config.h"
class dhtSensor{
public:
void begin();
void end();
void handle();
float Temperature();
float Humidity();
float temperature = 0;
float humidity = 0;
};