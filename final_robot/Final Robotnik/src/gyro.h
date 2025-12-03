#ifndef GYRO_H
#define GYRO_H
#include <Arduino.h>

extern bool gyro_ok;

void setupGyro();
float readGyro();
void flushGyro();

#endif


// #ifndef GYRO_H
// #define GYRO_H
// #include <Arduino.h>

// extern bool imu_ok;

// void setupGyro();
// float readGyro();

// #endif