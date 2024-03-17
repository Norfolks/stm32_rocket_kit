#include <SPI.h>
#include "printf.h"
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[5] = {0xEE,0xDD,0xCC,0xBB,0xAA};

void setup() {
  Serial.begin(9600);
  Serial.println("Start setup.");
  if(!radio.begin()) {
    Serial.println("Radio is not responding!!!!");
    while(1) {}
  }
  
  radio.setAutoAck(true);
  radio.setDataRate(1);

  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  printf_begin();
  radio.printDetails();
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[33] = ""; // Max size is 32 but last byte is for debug string ending.
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}