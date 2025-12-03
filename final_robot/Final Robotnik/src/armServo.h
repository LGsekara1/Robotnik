#ifndef ARM_SERVO_H
#define ARM_SERVO_H
#include <Arduino.h>
// #include <Servo.h>

void setupServo();
void getBox();
void releaseBox();

void ballVerticalUp();
void ballVerticalDown();
void ballCylinderIn();
void ballCylinderOut();
void ballHorizontalIn();
void ballHorizontalOut();


#endif