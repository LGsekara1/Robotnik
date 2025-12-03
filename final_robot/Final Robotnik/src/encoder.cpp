#include "encoder.h"
#include "pins.h"


volatile long pulses = 0;

void changePulses(){
  if (digitalRead(ENCODER_R2) == LOW) {pulses++;} 
  else {pulses--;}
}

void resetPulses() {
    noInterrupts();pulses = 0;interrupts();
}

long getPulses() {
    noInterrupts();long p = pulses;interrupts();
    return p;
}

float distance(){
  return (getPulses()*PI*65/224);
}