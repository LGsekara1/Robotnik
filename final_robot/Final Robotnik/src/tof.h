#ifndef TOF_H
#define TOF_H
#include <Arduino.h>

extern const int NUM_TOF_SENSORS;
extern int tof_values[6];

void setupToF();
void readToF();

#endif