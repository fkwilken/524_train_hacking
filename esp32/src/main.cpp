#include <SPI.h>
#include <RF24.h>
 
// these pins are the alternate SPI pins available for Teensy LC/3.0/3.1/3.2/3.5/3.6
#define MY_MISO 5
#define MY_MOSI 8
#define MY_SCLK 3
 
// notice these pin numbers are not the same used in the library examples
RF24 radio(7, 6); // the (ce_pin, csn_pin) connected to the radio

bool success_tx = false;

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
  radio.disableDynamicPayloads();
  radio.setChannel(40);   // Set Channel to 2440 MHZ
  radio.setAddressWidth(3);

  // uint8_t address [] = {0x76,0x24,0xDE,0x7F,0x10};   // Set RX Address
  // radio.openReadingPipe(0, address);  
  
  uint8_t address2 [] = {0,0,0};   // Set RX Address
  radio.openReadingPipe(1, address2); 


  uint8_t address3 [] = {0,0,0};   // Set TX Address
  radio.openWritingPipe(address3);

  Serial.println("Radio Began " + String(radio.isChipConnected()));
  radio.printDetails();

  radio.stopListening(); //ALWAYS call this before transmitting
 
  // ... continue with program as normal (see library examples/ folder)
}

//uint8_t wbuf2[] = {0xF0,0xF0,0xF0,0xF0};
uint8_t wbuf2[] = {0xF0,0xF0,0xDE,0xAD,0xBE,0xEF};
void loop() {
  //char buffer[33];

  /*Serial.print(".");*/

  // if (radio.available()) {      // is there a payload?
  //   radio.read(&buffer, 32);  // fetch payload from FIFO
  //   Serial.print(F("\nReceived: "));
  //   Serial.print(buffer);  // print the payload's value
  //   Serial.print(F(" - "));
  // }

  /*delay(100);*/

  // uint8_t wbuf[] = {0xDE,0xAD,0xBE,0xEF};
  // success_tx = radio.write(wbuf, sizeof(wbuf));

  success_tx = radio.write(wbuf2, sizeof(wbuf2));

  delay(500);



  // Serial.print("Success TX: ");
  // Serial.print(success_tx);
  // Serial.print(true);
  // Serial.println();

  static int i = 0;
  if (i++ == 50) {
    i = 0;
    radio.printDetails();
  }

  

}
