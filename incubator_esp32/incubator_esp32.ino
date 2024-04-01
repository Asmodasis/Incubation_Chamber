// Designed by Shawn Ray
// 3/11/2024

#include <WiFi.h>
//#include "driver/temperature_sensor.h"

int lightPin = 0;
int fanActivatePin = 0;
int heatPlateActivatePin = 0;

const char* ssid = "";
const char* password = "";

String hostname = "Incubation Chamber #1";

void initWifi(){
    // set the mode of the WiFi connector 
  WiFi.mode(WIFI_STA);
  // The name of the device
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname.c_str());
  // connect the wifi on the ESP32
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi...");
  // wait for WiFi conneciton.
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {

  // set up for USB communication
  Serial.begin(115200);
  delay(1000);

  initWiFi();
  // set pins for output
  // writing to the pins will set the state of the peripheral devices
  pinMode(lightPin,OUTPUT);
  pinMode(fanActivatePin,OUTPUT);
  pinMode(heatPlateActivatePin,OUTPUT);

}


void loop() {
  // put your main code here, to run repeatedly:
  int tempHighThresh = 100;
  int tempLowThresh = 40;
  int currentTemp = 0;
  //  activate heat plates
  if(currentTemp < tempLowThresh){
    digitalWrite(heatPlateActivatePin, HIGH);
    digitalWrite(fanActivatePin, HIGH);
  }else if(currentTemp > tempHighThresh){
    digitalWrite(heatPlateActivatePin, LOW);
    digitalWrite(fanActivatePin, HIGH);
  }else{
    digitalWrite(heatPlateActivatePin, LOW);
    digitalWrite(fanActivatePin, LOW);
  }

}

void activateFan(int pin){
  digitalWrite(pin, HIGH);
}

void deactivateFan(){
  digitalWrite(pin, HIGH);
}

void activateHeatPlates(){

}

void deactivateHeatPlates(){

}

void activateLights(){

}

void deactivateLights(){

}