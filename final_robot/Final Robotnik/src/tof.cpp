#include "tof.h"
#include "pins.h"

#include <Wire.h>
#include <VL53L0X.h>


const int NUM_TOF_SENSORS=6;
VL53L0X tof[NUM_TOF_SENSORS];
uint8_t addresses[NUM_TOF_SENSORS] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35};
int xshutPins[NUM_TOF_SENSORS] = {XSHUT_1, XSHUT_2, XSHUT_3, XSHUT_4, XSHUT_5, XSHUT_6};
int tof_values[NUM_TOF_SENSORS]={0};


void tof_indicator(){                             //error detection
  digitalWrite(indicator,HIGH);delay(1000);
  digitalWrite(indicator,LOW);delay(1000);
  digitalWrite(indicator,HIGH);
}


void setupToF(){
  Wire.begin();

  for (int i = 0; i < 6; i++) {  digitalWrite(xshutPins[i], LOW);}
  delay(20);

  for (int i = 0; i < 6; i++) {
    digitalWrite(xshutPins[i], HIGH);
    delay(20);
    if (!tof[i].init()) {tof_indicator();while (1);}
    tof[i].setAddress(addresses[i]);
    tof[i].setTimeout(30);
  }
}


void readToF(){
  for (int i = 0; i < 6; i++) {
    tof_values[i] = tof[i].readRangeSingleMillimeters();
    if (tof[i].timeoutOccurred()) tof_values[i] = -1;
  }
}

