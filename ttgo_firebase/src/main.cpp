#include <Arduino.h>
#include <SPI.h>
#include "esp32-hal-adc.h"

#include "../include/sensor/sensor.h"
#include "../include/firebaseLogin/firebaseLogin.h"

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60       /* Time ESP32 will go to sleep (in seconds) */

#define SET_SENSOR 0
#define SET_BOMBA 1

unsigned int time_bomb;
unsigned int time_sleep;
int choose = SET_SENSOR;
bool changedValue =0;
float valueTemperature=0;
String State_Bomb = "led";
String sensor = "value";
int sensor_Soil;

//FirebaseData ;

void setup()
{

  Serial.begin(115200);
   
  analogReadResolution(10); //12 bits
  pinMode(PIN_SOIL,INPUT_PULLUP);
  connectWifi();

  connectFire();

  time_bomb = getInt("time_bomb");
  time_sleep = getInt("time_sleep");
  
//Serial.println(readTemperature());
  
}

void loop() {


esp_sleep_enable_timer_wakeup(time_sleep * uS_TO_S_FACTOR);

setInt(sensor,sensorSoil());


  
    if(sensorSoil() > 800 && changedValue == 0)
    {
      digitalWrite(PIN_BOMB,1);
      Serial.println("Bomba ligada pelo sensor");
      changedValue = 0;
      setBool(State_Bomb,1);
      while(sensorSoil() > 800)
      {
        
        digitalWrite(PIN_BOMB,1);
        if(!getBool(State_Bomb))
        {
          digitalWrite(PIN_BOMB,0);
          break;
        }

      }
      setBool(State_Bomb,0); 
      setInt(sensor,sensorSoil());

    }else if (sensorSoil() < 800) {

      digitalWrite(PIN_BOMB,0);
      Serial.println("Bomba desligada pelo sensor");
      setInt(sensor,sensorSoil());
      //setBool(State_Bomb,0); 
    }
 
    if(getBool(State_Bomb))
    {
      setBool(State_Bomb,1); 
      digitalWrite(PIN_BOMB,1);
      changedValue = 1;
      Serial.println("Bomba ligada");
      delay(time_bomb);
      digitalWrite(PIN_BOMB,0);
      setBool(State_Bomb,0); 

     
    }else{
      setBool(State_Bomb,0); 
      digitalWrite(PIN_BOMB,0);
      changedValue = 0;
      Serial.println("Bomba desligada");
    
    }
  

  
  
  setInt(sensor,sensorSoil());
  digitalWrite(PIN_BOMB,0);

//delay(1000);
 //changedValue = getBool("led");
 
 //Serial.println(getFloat("value"));

//delay(1500);

if(getInt("time_sleep")!=0)
  esp_deep_sleep_start();

}