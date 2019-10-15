#include <Arduino.h>
#include "../include/sensor/sensor.h"



DHT_Unified dht(DHTPIN, DHTTYPE);
sensors_event_t event;
int sensorValue;

float readTemperature()
{
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    
    return 0;
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    return event.temperature;

  }
}

float readHumidity()
{
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
   return 0;
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));

    return event.relative_humidity;
  }
}

int sensorSoil ()
{
  sensorValue =0;
  for(int i =0; i<50; i++)
  {
    sensorValue += analogRead(PIN_SOIL);
    delay(10);
  }
  sensorValue = sensorValue/50;

  Serial.println("Valor sensor ");
  Serial.println(sensorValue);

  return sensorValue;
}
