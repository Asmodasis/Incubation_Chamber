// Designed by Shawn Ray
// 3/11/2024

//#include "driver/temperature_sensor.h"
int lightPin = 0;
int fanActivatePin = 0;
int heatPlateActivatePin = 0;


void setup() {

  // set up for USB communication
  Serial.begin(115200);

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