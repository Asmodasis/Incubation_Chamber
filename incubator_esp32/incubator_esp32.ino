// Designed by Shawn Ray
// 3/11/2024

//#include "driver/temperature_sensor.h"
int lightOnePin = 0;
int lightTwoPin = 0; 
int fanActivatePin = 0;
int heatPlateActivatePin = 0;


void setup() {

  // set up for USB communication
  Serial.begin(115200);

  // set pins for output
  // writing to the pins will set the state of the peripheral devices
  pinMode(lightOnePin,OUTPUT);
  pinMode(lightTwoPin,OUTPUT);
  pinMode(fanActivatePin,OUTPUT);
  pinMode(heatPlateActivatePin,OUTPUT);

}


void loop() {
  // put your main code here, to run repeatedly:

}

void activateFan(){

}

void deactivateFan(){

}

void activateHeatPlates(){

}

void deactivateHeatPlates(){

}

void activateLights(){

}

void deactivateLights(){

}