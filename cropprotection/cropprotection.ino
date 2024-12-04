int Status = 4;  // Digital pin D6

int sensor = 16;  // Digital pin D7
int sensor1 = 5;  // Digital pin D7
int state=0;
int state1=0;
int ss=0;
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = "AndroidAP";   // your network SSID (name) 
char pass[] = "rjzf4543";    // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 2050444;
const char * myWriteAPIKey = "WIIHHZZ6BYXF7VZP";

int number = 0;

void setup() {
 pinMode(sensor, INPUT);   // declare sensor as input
   pinMode(sensor1, INPUT); 
  pinMode(Status, OUTPUT);  // declare LED as output
  Serial.begin(9600);
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, ss, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

   state = digitalRead(sensor);
     state1 = digitalRead(sensor1);
    if((state == HIGH)||(state == HIGH)) {
      ss=1;
      digitalWrite (Status, HIGH);
      delay(100);
      digitalWrite (Status, LOW);
      Serial.println("Motion detected!");
      delay(1000);
    }
    else {
      ss=0;
      digitalWrite (Status, LOW);
      Serial.println("Motion absent!");
      delay(1000);
      }
  delay(5000); // Wait 20 seconds to update the channel again
}
