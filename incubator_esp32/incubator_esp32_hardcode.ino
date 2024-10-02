// Designed by Shawn Ray
// 3/11/2024


#define convertTime(a,b) ( (int)( (double) (a - b) / 3.6*pow(10,6)) )
const int tempSensorPin = 36;
const int lightPin = 11;
const int fanActivatePin = 12;
const int heatPlateActivatePin = 13;

//String hostname = "Incubation Chamber #1";
unsigned long programStartTime;

// used for testing
int testValue = 0;

int dayTempHigh = 28;
int dayTempLow = 18;
int nightTempHigh = 28;
int nightTempLow = 18;

int currentTemp = 0;
int hourLimit = 8;


void setup() {

  // Log start time of the program
  programStartTime = millis();

  // set up for USB communication
  Serial.begin(115200);
  delay(1000);

  // set pins for output
  // writing to the pins will set the state of the peripheral devices
  pinMode(lightPin,OUTPUT);
  pinMode(fanActivatePin,OUTPUT);
  pinMode(heatPlateActivatePin,OUTPUT);
  pinMode(tempSensorPin,INPUT);

  // The lights start on (beginning of the day)
  digitalWrite(lightPin, HIGH);
}


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
  currentTemp = analogRead(tempSensorPin);
  Serial.print(currentTemp);
  delay(1000);
                                // DayTime
  if(hours < 12){

    digitalWrite(lightPin, HIGH);
      //  activate heat plates
      //  activate the fan
    if(currentTemp < dayTempLow){
      digitalWrite(heatPlateActivatePin, HIGH);
      digitalWrite(fanActivatePin, HIGH);
    }else if(currentTemp > dayTempHigh){
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
    if(currentTemp < nightTempLow){
      digitalWrite(heatPlateActivatePin, HIGH);
      digitalWrite(fanActivatePin, HIGH);
    }else if(currentTemp > nightTempHigh){
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
