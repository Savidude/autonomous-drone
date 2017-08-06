#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

const int trigPin = 2, echoPin = 3;
long duration;

void setup(void){
  Serial.begin(9600);
  radio.begin(); radio.openWritingPipe(pipe);
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT); 
}

void loop(void){
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 5400);
  msg[0] = duration*0.034/2;
  Serial.println(msg[0]);
  radio.write(msg, 1);
}
