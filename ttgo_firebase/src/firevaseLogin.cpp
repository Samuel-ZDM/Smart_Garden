#include "../include/firebaseLogin/firebaseLogin.h"
FirebaseData firebaseData;


void connectWifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void connectFire()
{
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   Serial.println("Teste");
   Firebase.reconnectWiFi(true);
   Serial.println("Teste2");
}

bool getBool(String value)
{

 if (Firebase.getBool(firebaseData, value)) 
 {
   Serial.println(firebaseData.boolData());
  
    return firebaseData.boolData();
    
  } else {
    Serial.println(firebaseData.errorReason());
    Serial.println("Erro get bool");
    return -1;
  }

}

int getInt(String value)
{
    if (Firebase.getInt(firebaseData, value ))
    {
      Serial.println(firebaseData.intData());
      return firebaseData.intData();
    }
    return 0;
}

float getFloat(String value)
{
    if (Firebase.getFloat(firebaseData, value))
    {
      Serial.println(firebaseData.floatData());
      return firebaseData.floatData();
    }
    return 0;
}

void setFloat(String value, float sensor)
{
    if (Firebase.setFloat(firebaseData, value , sensor)) 
    {
      Serial.println(firebaseData.floatData());
    }
}

void setInt(String value, int sensor)
{
    if (Firebase.setInt(firebaseData, value , sensor)) 
    {
      Serial.println(firebaseData.intData());
    }
}

void setBool(String value, bool sensor)
{
   if (Firebase.setBool(firebaseData, value , sensor)) 
    {
      Serial.println(firebaseData.boolData());
    }
}