#define DATA_READ_ENABLE 8
#include <HardwareSerial.h>

// USE ARDUINO based device to relay bluetooth serial connection at the highest supported speed (Bluetooth HC-05 device)
size_t    inputCount;
size_t    outputCount;

// INPUT:  Bluetooth (Serial) Byte Datastream (1382400 Baud)
// OUTPUT: USB Byte Datastream (1382400 Baud)
char*   inputBuffer;
char*   outputBuffer;

void setup() {                
  // initialize the READ_ENABLE pin (must be toggled to signal read)
  pinMode(DATA_READ_ENABLE,OUTPUT);
  
  // To support 1382400 speed you must configure the device properly using AT Command mode
  Serial.begin(1382400 );
  Serial1.begin(1382400);
  
  // set timeout for byte reads (50 ms) 
  Serial.setTimeout(50);
  Serial1.setTimeout(50);
  
  // initialize buffers and index
  inputBuffer = new char[201];
  outputBuffer = new char[201];
  
  inputBuffer[200] = '\0';
  outputBuffer[200] = '\0';
  
  outputCount = 0;
  inputCount = 0;
}

// the loop routine runs over and over again forever:
// For Each loop
//  -If USB has data to send to the bluetooth
//    -Read all bytes available
//    -Write all output bytes to Bluetooth device
//  -Toggle The DATA_READ_ENABLE pin for the HC-05 device (connected on pin 8)
//  -If Bluetoth has data to send to the USB serial device
//    -Read all bytes available
//    -Write all input bytes to USB Serial port
//  -- REPEAT
void loop() {
  if(Serial.available())
  {
    outputCount = Serial.readBytes(outputBuffer,200);
    outputBuffer[outputCount] = '\0';
    Serial1.write(outputCount);
  }
  digitalWrite(DATA_READ_ENABLE, HIGH);    // toggle Read flag for bluetooth
  digitalWrite(DATA_READ_ENABLE, LOW);
  if(Serial1.available())
  {
    inputCount = Serial1.readBytes(inputBuffer,200);
    inputBuffer[inputCount] = '\0';
    Serial.write(inputBuffer);
  }
}

