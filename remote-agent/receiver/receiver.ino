#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg[1];
int spd;
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int up = 6;
int down = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()){
      radio.read(msg, 1);      
      Serial.println(msg[0]);
      if (msg[0]>60){
        analogWrite(up,0);
        delay(10);
        if (msg[0]>100){
          msg[0] = 100;
        }
        spd = 255*(msg[0]-60)/40;
        analogWrite(down,spd);
      }else{
        analogWrite(down,0);
        delay(10);
        if (msg[0]<20){
          msg[0]=20;
        }
        spd = 255*(60-msg[0])/40;
        analogWrite(up,spd);
      }
  }else{
    Serial.println("No radio available");
  }
}
