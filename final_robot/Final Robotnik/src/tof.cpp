#include "tof.h"
#include "pins.h"
#include "display.h"

#include <Wire.h>
#include <VL53L0X.h>


const int NUM_TOF_SENSORS=7;
VL53L0X tof[NUM_TOF_SENSORS];
uint8_t addresses[NUM_TOF_SENSORS] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36};
int xshutPins[NUM_TOF_SENSORS] = {XSHUT_1, XSHUT_2, XSHUT_3, XSHUT_4, XSHUT_5, XSHUT_6, XSHUT_7};
float tof_values[NUM_TOF_SENSORS]={0};


void tof_error_indicator(int i){                             //error detection
  digitalWrite(indicator,HIGH);delay(1000);
  digitalWrite(indicator,LOW);delay(1000);
  digitalWrite(indicator,HIGH);
  // showDisplay("Error:",2,0,0);
  // showDisplay("ToF"+String(i+1),2,0,30);
}


void setupToF(){
  // Wire.begin();

  for (int i = 0; i < NUM_TOF_SENSORS; i++) {  digitalWrite(xshutPins[i], LOW);}
  delay(20);

  for (int i = 0; i < NUM_TOF_SENSORS; i++) {
    digitalWrite(xshutPins[i], HIGH);
    delay(20);
    if (!tof[i].init()) {tof_error_indicator(i);Serial.print("ToF Error ");Serial.println(i+1);}
    else {Serial.print("ToF Sensor initialized ");Serial.println(i+1);}
    tof[i].setAddress(addresses[i]);
    tof[i].setMeasurementTimingBudget(20000);
    tof[i].startContinuous();
  }
}




// void readToF(){
//   float distance;
//   for (int i = 0; i < NUM_TOF_SENSORS; i++) {
//     // tof_values[i] = tof[i].readRangeSingleMillimeters();
//     distance = tof[i].readRangeContinuousMillimeters();
//     if (distance == 8191.0) distance = 1200.0; //0 means no object detected
//     if (i==0) tof_values[i]=distance - 55; 
//     if (i==1) tof_values[i]=distance - 40;
//     if (i==2) tof_values[i]=distance - 30;
//     if (i==3) tof_values[i]=distance - 35;
//     if (i==4) tof_values[i]=distance - 17;
//     if (i==5) tof_values[i]=distance - 45;
//     if (i==6) tof_values[i]=distance - 5;
//     if (tof[i].timeoutOccurred()) tof_values[i] = -1;
//     Serial.print(distance); Serial.print("  ");
//   }
//   Serial.println();
// }


void readToF() {
    const float offsets[NUM_TOF_SENSORS] = {55, 40, 30, 35, 17, 45, 5};
    const float MAX_RANGE = 1200.0f;
    
    for (int i = 0; i < NUM_TOF_SENSORS; i++) {
        float distance = tof[i].readRangeContinuousMillimeters();
        
        if (tof[i].timeoutOccurred() || distance == 0) {
            tof_values[i] = -1;
            Serial.print("ERR ToF\t");
        }
        else if (distance >= 1200.0f) {
            tof_values[i] = MAX_RANGE;
            Serial.print("MAX\t");
        }
        else {
            tof_values[i] = distance - offsets[i];
            if (tof_values[i] < 0) tof_values[i] = 0;
            Serial.print(tof_values[i]); Serial.print("\t");
        }
    }
    Serial.println();
}



void flushToF() {
    for (int i = 0; i < 10; i++) {
        readToF();
        delay(5);
    }
}




















// #include "tof.h"
// #include "pins.h"
// #include "display.h"

// #include <Wire.h>
// #include <VL53L0X.h>


// const int NUM_TOF_SENSORS=7;
// VL53L0X tof[NUM_TOF_SENSORS];
// uint8_t addresses[NUM_TOF_SENSORS] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36};
// int xshutPins[NUM_TOF_SENSORS] = {XSHUT_1, XSHUT_2, XSHUT_3, XSHUT_4, XSHUT_5, XSHUT_6, XSHUT_7};
// float tof_values[NUM_TOF_SENSORS]={0};


// void tof_error_indicator(int i){                             //error detection
//   digitalWrite(indicator,HIGH);delay(1000);
//   digitalWrite(indicator,LOW);delay(1000);
//   digitalWrite(indicator,HIGH);
//   // showDisplay("Error:",2,0,0);
//   // showDisplay("ToF"+String(i+1),2,0,30);
// }


// void setupToF(){
//   // Wire.begin();

//   for (int i = 0; i < NUM_TOF_SENSORS; i++) {  digitalWrite(xshutPins[i], LOW);}
//   delay(20);

//   for (int i = 0; i < NUM_TOF_SENSORS; i++) {
//     digitalWrite(xshutPins[i], HIGH);
//     delay(20);
//     if (!tof[i].init()) {tof_error_indicator(i);Serial.print("ToF Error");Serial.println(i+1);}
//     else {Serial.print("ToF Sensor initialized");Serial.println(i+1);}
//     tof[i].setAddress(addresses[i]);
//     // tof[i].setTimeout(50);
//     tof[i].setMeasurementTimingBudget(20000);
//     tof[i].startContinuous();
//   }
// }




// void readToF(){
//   float distance;
//   for (int i = 0; i < NUM_TOF_SENSORS; i++) {
//     // tof_values[i] = tof[i].readRangeSingleMillimeters();
//     distance = tof[i].readRangeContinuousMillimeters();
//     if (distance == 8191.0) distance = 1200.0; //0 means no object detected
//     if (i==0) tof_values[i]=distance - 55; 
//     if (i==1) tof_values[i]=distance - 40;
//     if (i==2) tof_values[i]=distance - 30;
//     if (i==3) tof_values[i]=distance - 35;
//     if (i==4) tof_values[i]=distance - 17;
//     if (i==5) tof_values[i]=distance - 45;
//     if (i==6) tof_values[i]=distance - 5;
//     if (tof[i].timeoutOccurred()) tof_values[i] = -1;
//   }
// }





















// #include "tof.h"
// #include "pins.h"

// #include <Wire.h>
// #include <VL53L0X.h>


// const int NUM_TOF_SENSORS=6;
// VL53L0X tof[NUM_TOF_SENSORS];
// uint8_t addresses[NUM_TOF_SENSORS] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35};
// int xshutPins[NUM_TOF_SENSORS] = {XSHUT_1, XSHUT_2, XSHUT_3, XSHUT_4, XSHUT_5, XSHUT_6};
// int tof_values[NUM_TOF_SENSORS]={0};


// void tof_indicator(){                             //error detection
//   digitalWrite(indicator,HIGH);delay(1000);
//   digitalWrite(indicator,LOW);delay(1000);
//   digitalWrite(indicator,HIGH);
// }


// void setupToF(){
//   Wire.begin();

//   for (int i = 0; i < 6; i++) {  digitalWrite(xshutPins[i], LOW);}
//   delay(20);

//   for (int i = 0; i < 6; i++) {
//     digitalWrite(xshutPins[i], HIGH);
//     delay(20);
//     if (!tof[i].init()) {tof_indicator();while (1);}
//     tof[i].setAddress(addresses[i]);
//     tof[i].setTimeout(30);
//   }
// }


// void readToF(){
//   for (int i = 0; i < 6; i++) {
//     tof_values[i] = tof[i].readRangeSingleMillimeters();
//     if (tof[i].timeoutOccurred()) tof_values[i] = -1;
//   }
// }

