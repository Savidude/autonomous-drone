#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int up = 5; int down = 6; int spd;
int RemPwr = 30; int Tune = 40; 

void setup(void){
  Serial.begin(9600);
  radio.begin(); radio.openReadingPipe(1,pipe); radio.startListening();
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  setPwmFrequency(up, 8);
  setPwmFrequency(down, 8);
}
 
void loop(void){
  if (Serial.available() == 1){
    Tune = Serial.parseInt(); 
  }
  
 if (radio.available()){
    bool done = false;    
    while (!done){
      done = radio.read(msg, 1);      
      Serial.println(msg[0]);
      //delay(10);
    }
//    msg[0]=40;
    
    if(msg[0]>40){
      analogWrite(up,0);
      delay(1);
      spd = RemPwr*(msg[0]-40)/Tune;
      if (spd>RemPwr){spd=RemPwr;}
      analogWrite(down,spd);
    }else if(msg[0]<40 && msg[0]>0){
      analogWrite(down,0);
      delay(1);
      spd = RemPwr*(40-msg[0])/Tune; 
      if (spd>RemPwr){spd=RemPwr;}
      analogWrite(up,spd);           
    }else{
      analogWrite(up,0);
      analogWrite(down,0);
    }
            
  }
  else{
//    Serial.println("No radio available");
//    analogWrite(up,0);
//    analogWrite(down,0);    
  }
}








void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
