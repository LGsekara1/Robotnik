#ifndef ENCODER_H
#define ENCODER_H
#include <Arduino.h>

extern volatile long pulses;
void changePulses();
void resetPulses();
long getPulses();

#endif