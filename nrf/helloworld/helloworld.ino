#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup() {
  Serial.begin(57600);
  printf_begin();

  radio.begin();
  radio.setRetries(15,15);

  radio.setPayloadSize(8);

  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);

  radio.stopListening();

  radio.printDetails();
  

}

void loop() {
    char* message = "Hello World";
    printf("Now sending %lu...",message);
    bool ok = radio.write( message, sizeof(char *) );
    
    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");

}
