
// most launchpads have a red LED
#define LED 9
#define DATA_READ_ENABLE 8
#include <HardwareSerial.h>




void setup() {                
  // initialize the digital pin as an output.
  pinMode(DATA_READ_ENABLE,OUTPUT);
  digitalWrite(DATA_READ_ENABLE,HIGH);
  Serial.begin(9600);
  Serial1.begin(38400);
  Serial.println("Enter AT Commands:");
}

// the loop routine runs over and over again forever:
void loop() {
  
  if(Serial1.available()) 
    Serial.write(Serial1.read());
    
  if(Serial.available())
    Serial1.write(Serial.read());
}

