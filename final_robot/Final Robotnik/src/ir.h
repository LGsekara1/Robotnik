#ifndef IR_H
#define IR_H
#include <Arduino.h>

extern const int NUM_IR_SENSORS;
extern int ir_values[8];

void readIR();

#endif