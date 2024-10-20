#include "Values.h"
DHTesp dht;
void dhtSensor::begin()
{
    dht.setup(DHT_SCL_PIN, DHTesp::DHT22);
}

void dhtSensor::end()
{
}

void dhtSensor::handle()
{
    delay(dht.getMinimumSamplingPeriod());
}

float dhtSensor::Temperature()
{
    return temperature = dht.getTemperature();
}

float dhtSensor::Humidity()
{
    return humidity = dht.getHumidity();
}
