#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

void setup()
{
    Serial.begin(115200);
    pinMode (LED_PIN, OUTPUT)
    if (IS_WOKWI) 
        WiFi.begin(SSID, PASS, CHANNEL);
    else 
        WiFi.begin(SSID, PASS);

   while (WiFi.status() != WL_CONNECTED) 
    {
      delay(250);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
     if (WiFi.status() == WL_CONNECTED)
     {
        HTTPClient http;
        String Path = String(ENDPOINT) + "/api/light";
        http.begin(Path.c_str());
        http.addHeader("api-key", API_KEY);

        int Code_Response = http.Get();
        
        if (Code_Response >=0)
        {
            Serial.print("HTTP Response Code:");
            Serial.println(Code_Response);
            String feedback = http.getString();
            Serial.println(feedback);

            JsonDocument<200> doc;
            DeserializationError error = deserializeJson (doc, feedback);
            if (error)
            {
              Serial.print("Deserialization failed: ");
              Serial.println(error.c_str());
              return;
            } 
            bool led_status = doc["light"];
            if(led_status) 
            {
                digitalWrite(LED_PIN, HIGH);
            }     
            else
            {
                digitalWrite(LED_PIN, LOW);
            }
            
        }
        http.end();

        HTTPClient http;
        String PATH = String(ENDPOINT)+"/api/temp";
        http.begin(PATH.c_str());
        http.addHeader("api-key", API_KEY);
        
        float temperature = 25.5;
        JsonDocument<200> doc;
        doc["temp"] = temperature;
        String request;
        serializeJson (doc, request);

        int Responsecode = http.PUT(request);
        if (Responsecode >= 0)
        {
            Serial.print("HTTP Response Code:");
            Serial.println(Code_Response);
            String response = http.getString();
            Serial.println(response);
        }
        http.end();
    }

}
