/*
  Arduino Wireless Communication Tutorial
        Example 1 - Receiver Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte nodeAddress[5] = {'N', 'O', 'D', 'E', '1'};
byte tosend[32];

bool ready_to_send = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(90);
  radio.setCRCLength(RF24_CRC_8);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(nodeAddress);
  radio.stopListening();
}

void loop() {
  memset(tosend, 0, sizeof(tosend));
  byte inc;
  int counter = 0;
  inc = Serial.read();
  if (inc == '<') {
    digitalWrite(LED_BUILTIN, HIGH); 
    tosend[counter] = inc;
    counter++;
    while (true) {
      inc = Serial.read();
      if(inc == -1) continue;
      tosend[counter] = inc;
      if (inc == '>') {
        radio.write(&tosend, sizeof(tosend));
        digitalWrite(LED_BUILTIN, LOW);
        break;
      }
      counter++;
    }
  }
  delay(100);
}
