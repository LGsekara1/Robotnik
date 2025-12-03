#include "gyro.h"
#include "display.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// IMU
Adafruit_BNO055 bno=Adafruit_BNO055(55, 0x28, &Wire);
// Adafruit_BNO055 bno;
bool gyro_ok = false;

void gyro_error_indicator(){                             //error detection
  // showDisplay("Error:",2,0,0);
  // showDisplay("Gyro",2,0,30);
  for (int i=0;i<5;i++){
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(500);
  }
}

void setupGyro() {
  gyro_ok = bno.begin();
  delay(1000);
  if (gyro_ok) {
    bno.setExtCrystalUse(true);
    flushGyro();
  }
  else {gyro_error_indicator();}
}

float readGyro() {
  // if (!imu_ok) return 0;
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  return orientationData.orientation.x;
}

void flushGyro() {
  for (int i = 0; i < 5; i++) {
    readGyro();delay(10);
  }
}







// #include "gyro.h"

// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BNO055.h>

// // IMU
// Adafruit_BNO055 bno=Adafruit_BNO055(55, 0x29, &Wire);
// // Adafruit_BNO055 bno;
// bool imu_ok = false;

// void setupGyro() {
//   imu_ok = bno.begin();
//   delay(1000);
//   if (imu_ok) {
//     bno.setExtCrystalUse(true);
//   }
// }

// float readGyro() {
//   // if (!imu_ok) return 0;
//   sensors_event_t orientationData;
//   bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
//   return orientationData.orientation.x;
// }