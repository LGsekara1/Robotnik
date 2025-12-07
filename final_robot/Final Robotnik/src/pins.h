#ifndef PINS_H
#define PINS_H

#include <Arduino.h>
// #include "motion.h"


const int indicator =13;
// Motor Pins
const int L_LPWM = 9;
const int L_RPWM = 10;
const int R_LPWM = 6;
const int R_RPWM = 7;

const int ENCODER_L1=3;  //yellow
const int ENCODER_L2=38;  //2;  //green
const int ENCODER_R2=39; //18; //yellow
const int ENCODER_R1=19; //green

const int BOX_SERVO_VERTICAL_PIN = 5;
const int BOX_SERVO_HORIZONTAL_PIN = 4;
const int BALL_SERVO_VERTICAL_PIN= 12;
const int BALL_SERVO_HORIZONTAL_PIN= 11;
const int BALL_SERVO_CYLINDER_PIN= 13;


const int IRSensorPinsDigital[8]={22, 23, 24, 25, 26, 27, 28, 29};
const int IRSensorPinsAnalog[8] = {A0,A1,A2,A3,A4,A5,A6,A7};

const int XSHUT_1 = 41;//41
const int XSHUT_2 = 42; //40
const int XSHUT_3 = 40; //43
const int XSHUT_4 = 43;//42
const int XSHUT_5 = 45;//45
const int XSHUT_6 = 44;//44
const int XSHUT_7 = 53; //39

const int COLOR1_S0 = 30;
const int COLOR1_S1 = 31;
const int COLOR1_S2 = 32;
const int COLOR1_S3 = 33;
const int COLOR1_OUT = 34;

const int COLOR2_S0 =A8;
const int COLOR2_S1 =A9;
const int COLOR2_S2 =A10;
const int COLOR2_S3 =A11;
const int COLOR2_OUT =A12;

const int GYRO_INTERRUPT_PIN = 2; 

const int SHARP_IR_PIN=A0;

const int IRSensorPinLeft=A1;
const int IRSensorPinRight=A2;




//pins setup
void setupPins();

#endif