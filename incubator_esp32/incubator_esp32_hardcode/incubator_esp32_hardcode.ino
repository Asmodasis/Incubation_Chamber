// Designed by Shawn Ray
// 3/11/2024

#include <OneWire.h>
#include <DallasTemperature.h>

#define convertTime(a,b) ( (int)( (double) (a - b) / 3.6*pow(10,6)) )
const int tempSensorPin = 9;
const int lightPin = 11;
const int fanActivatePin = 12;
const int heatPlateActivatePin = 13;

//String hostname = "Incubation Chamber #1";
unsigned long programStartTime;

// used for testing
int testValue = 0;

int dayTempHigh = 20;
int dayTempLow = 18;
int nightTempHigh = 12;
int nightTempLow = 8;

float tempCelsius;    // current temperature in Celsius
float tempFahrenheit; // current temperature in Fahrenheit

int hourLimit = 8;

OneWire oneWire(tempSensorPin);         // setup a oneWire instance 
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library

void setup() {

  // Log start time of the program
  programStartTime = millis();

  // set up for USB communication
  Serial.begin(115200);
  delay(1000);

  // set pins for output
  // writing to the pins will set the state of the peripheral devices
  pinMode(lightPin, OUTPUT);
  pinMode(fanActivatePin, OUTPUT);
  pinMode(heatPlateActivatePin, OUTPUT);
  pinMode(tempSensorPin, INPUT);
  sensors.begin();    // initialize the sensor

  // The lights start on (beginning of the day)
  digitalWrite(lightPin, HIGH);
}
/*void loop(){
  digitalWrite(lightPin, LOW);
  digitalWrite(fanActivatePin, LOW);
  digitalWrite(heatPlateActivatePin, HIGH);
}*/

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long currentTime = millis();
  //unsigned long currentMillis = millis();
  unsigned long seconds = (currentTime-programStartTime) / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  unsigned long days = hours / 24;
  //currentMillis %= 1000;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;
  sensors.requestTemperatures();
  tempCelsius = sensors.getTempCByIndex(0);
  tempFahrenheit = tempCelsius * 9 / 5 + 32;

  Serial.print("Temperature in Celcius: ");
  Serial.println(tempCelsius);
  Serial.print("Temperature in Fahrenheit: ");
  Serial.println(tempFahrenheit);

  delay(5000);
  for(int i = 0; i < 16; ++i){
    Serial.print("\n");
  }
  delay(1000);
                                // DayTime
  if(hours < 12){

    digitalWrite(lightPin, HIGH);
      //  activate heat plates
      //  activate the fan
    if(tempCelsius < dayTempLow){
      digitalWrite(heatPlateActivatePin, HIGH);
      digitalWrite(fanActivatePin, HIGH);
    }else if(tempCelsius > dayTempHigh){
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
  }else if(hours > 12){         // Nighttime

    digitalWrite(lightPin, LOW);
      //  activate heat plates
      //  activate the fan
    if(tempCelsius < nightTempLow){
      digitalWrite(heatPlateActivatePin, HIGH);
      digitalWrite(fanActivatePin, HIGH);
    }else if(tempCelsius > nightTempHigh){
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

}
