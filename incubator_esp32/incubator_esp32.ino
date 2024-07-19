// Designed by Shawn Ray
// 3/11/2024

#include <WiFi.h>
//#include <Visualizer/Temperature_Reader.py>
//#include "driver/temperature_sensor.h"

int lightPin = 0;
int fanActivatePin = 0;
int heatPlateActivatePin = 0;

const char* ssid = "Ray-net";
const char* password = "Jumble2o2";
// the address of the machine running the python script
const char* ServerIPaddress = "192.168.168.42";

String hostname = "Incubation Chamber #1";
unsigned long programStartTime;


void initWiFi(){
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
    Serial.println('Connecting...');
    delay(1000);
  }
  Serial.println('Connected.');
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());

}

void setup() {

  // Log start time of the program
  programStartTime = millis();

  // set up for USB communication
  Serial.begin(115200);
  delay(1000);

  initWiFi();
  // set pins for output
  // writing to the pins will set the state of the peripheral devices
  pinMode(lightPin,OUTPUT);
  pinMode(fanActivatePin,OUTPUT);
  pinMode(heatPlateActivatePin,OUTPUT);
  // The lights start on (beginning of the day)
  digitalWrite(lightPin, HIGH);
}


void loop() {
  // put your main code here, to run repeatedly:

  WiFiClient client;
  if(!client.connect(ServerIPaddress, 8090)){      
    Serial.println("Connection to host failed");
    delay(1000);
    return;
  }
  Serial.println("client connected sending packet");    // <<< added
  client.print("Hello from ESP32!");
  client.stop();
  delay(1000);
  int tempHighThresh = 100;
  int tempLowThresh = 40;
  int currentTemp = 0;
  int hourLimit = 8;
  unsigned long currentTime = millis();
  /*
  Code Segment manages the lights on a start and end time basis. UTC-8 time zone 
  */
  // convert the elapsed time to hours
  if( ( (int)( (double) (currentTime - programStartTime) / 3.6*pow(10,6)) >= hourLimit ) ){
    // turn the lights off
    digitalWrite(lightPin, LOW);
  }

  /*
  Code Segment manages the temperature of the incubation chamber by thresholding a low and high temperature rating
  */
    //  activate heat plates
    //  activate the fan
  if(currentTemp < tempLowThresh){
    digitalWrite(heatPlateActivatePin, HIGH);
    digitalWrite(fanActivatePin, HIGH);
  }else if(currentTemp > tempHighThresh){
    //  deactivate heat plates
    //  activate the fan
    digitalWrite(heatPlateActivatePin, LOW);
    digitalWrite(fanActivatePin, HIGH);
  }else{
    //  deactivate heat plates
    //  deactivate the fan
    digitalWrite(heatPlateActivatePin, LOW);
    digitalWrite(fanActivatePin, LOW);
  }

}

void activateFan(int pin){
  digitalWrite(pin, HIGH);
}

void deactivateFan(int pin){
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