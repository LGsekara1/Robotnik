#ifndef MOTION_H
#define MOTION_H
#include <Arduino.h>

// void initIMU();
void startMotors(int leftSpeed,int rightSpeed);
void stopMotors();
void rotateRobot(char direction, float target_angle);

// extern int pulses;
void check();
void goDistance(float distance);
void nodeTraversal();

#endif
