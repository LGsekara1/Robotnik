#ifndef TOF_H
#define TOF_H
#include <Arduino.h>

#include <VL53L0X.h>

extern const int NUM_TOF_SENSORS;
extern float tof_values[7];

extern int xshutPins[7];
// extern VL53L0X tof[6];

void setupToF();
void readToF();

#endif



// #ifndef TOF_H
// #define TOF_H
// #include <Arduino.h>

// extern const int NUM_TOF_SENSORS;
// extern int tof_values[6];

// void setupToF();
// void readToF();

// #endif