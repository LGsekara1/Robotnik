#ifndef IR_H
#define IR_H
#include <Arduino.h>

extern const int NUM_IR_SENSORS;
extern int ir_values[8];

void readIR();
void calibrateIR();
// void setupCalibrateIR();

bool allZeros(int arr[], int size);
bool allOnes(int arr[], int size);
bool isNextNode();
bool isJunction();
bool isWhiteLine();

#endif



// #ifndef IR_H
// #define IR_H
// #include <Arduino.h>

// extern const int NUM_IR_SENSORS;
// extern int ir_values[8];

// void readIR();
// void calibrateIR();
// void setupCalibrateIR();

// #endif




// #ifndef IR_H
// #define IR_H
// #include <Arduino.h>

// extern const int NUM_IR_SENSORS;
// extern int ir_values[8];

// void readIR();

// #endif