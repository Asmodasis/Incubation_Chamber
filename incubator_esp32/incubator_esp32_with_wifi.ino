// Designed by Shawn Ray
// 3/11/2024

#include <WiFi.h>
#define convertTime(a,b) ( (int)( (double) (a - b) / 3.6*pow(10,6)) )
int lightPin = 0;
int fanActivatePin = 0;
int heatPlateActivatePin = 0;

const char* ssid = "bar";
const char* password = "foo";
// the address of the machine running the python script
const char* ServerIPaddress = "192.168.168.42";
// the address of the chamber 
IPAddress chamberIp(192, 168, 168, 182);

String hostname = "Incubation Chamber #1";
unsigned long programStartTime;

// used for testing
int testValue = 0;
int tempHighThresh = 28;
int tempLowThresh = 18;

int currentTemp = 0;
int hourLimit = 8;
void initWiFi(){
  // set the mode of the WiFi connector 
  WiFi.mode(WIFI_STA);
  // The name of the device
  WiFi.config(chamberIp, INADDR_NONE, INADDR_NONE, INADDR_NONE);
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

  if(client.connect(ServerIPaddress, 8090)){   
    // Send temp and device data to the server for display   
    //client.print("Hello from ESP");
    if(!testValue){
    client.print(String(tempHighThresh)+','+String(tempLowThresh)+','+String(currentTemp)+','+String(hourLimit)+','+String(hours));
    tempHighThresh = 90; // REMOVE
    tempLowThresh = 50; // REMOVE
    currentTemp = 0; // REMOVE
    hourLimit = 9; // REMOVE
    testValue = testValue  + 1; // REMOVE
    delay(1000);
    }else{
      client.print(String(tempHighThresh)+','+String(tempLowThresh)+','+String(currentTemp)+','+String(hourLimit)+','+String(hours)); // REMOVE
      testValue = 0; // REMOVE
    }
    
    return;
  }
 
  /*
  Code Segment manages the lights on a start and end time basis. UTC-8 time zone 
  */
  // convert the elapsed time to hours
  if( hours >= hourLimit ){
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
