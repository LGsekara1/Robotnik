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

const int IRSensorPins[8] = {22, 23, 24, 25, 26, 27, 28, 29};

const int ENCODER_L1=3;  //yellow
const int ENCODER_L2=2;  //green
const int ENCODER_R2=18; //yellow
const int ENCODER_R1=19; //green


const int XSHUT_1 = 41;
const int XSHUT_2 = 40;
const int XSHUT_3 = 43;
const int XSHUT_4 = 42;
const int XSHUT_5 = 45;
const int XSHUT_6 = 44;



//pins setup
void setupPins();

#endif