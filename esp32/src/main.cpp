#include <SPI.h>
#include <RF24.h>
 
// these pins are the alternate SPI pins available for Teensy LC/3.0/3.1/3.2/3.5/3.6
#define MY_MISO 5
#define MY_MOSI 8
#define MY_SCLK 3
 
// notice these pin numbers are not the same used in the library examples
RF24 radio(7, 6); // the (ce_pin, csn_pin) connected to the radio
 
void setup() {
  
  Serial.begin(115200);
  Serial.println("Setup!!");
  // while (!Serial) {} //some boards need this
 
  SPI.begin(MY_SCLK, MY_MISO, MY_MOSI);

  if (!radio.begin()) {
    Serial.println("radio hardware not responding!!");
    // while (1) {} // hold program in infinite loop to prevent subsequent errors
  } 

  // Setup
  radio.disableCRC();     // Disable CRC Checking
  radio.setChannel(44);   // Set Channel to 2440 MHZ

  uint8_t address [] = {0xff,0xff,0xff};   // Set RX Address
  radio.setAddressWidth(3);
  // radio.setPayloadSize()
  radio.openReadingPipe(0, address);  

  radio.startListening(); // Listen on

  Serial.println("Radio Began " + String(radio.isChipConnected()));
  radio.printDetails();
 
  // ... continue with program as normal (see library examples/ folder)
}

void loop() {
  char buffer[33];

  Serial.print(".");

  if (radio.available()) {      // is there a payload?
    radio.read(&buffer, 32);  // fetch payload from FIFO
    Serial.print(F("\nReceived: "));
    Serial.print(buffer);  // print the payload's value
    Serial.print(F(" - "));
  }

  delay(100);

}