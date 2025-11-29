#include "gyro.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// IMU
Adafruit_BNO055 bno=Adafruit_BNO055(55, 0x29, &Wire);
// Adafruit_BNO055 bno;
bool imu_ok = false;

void setupGyro() {
  imu_ok = bno.begin();
  delay(1000);
  if (imu_ok) {
    bno.setExtCrystalUse(true);
  }
}

float readGyro() {
  // if (!imu_ok) return 0;
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  return orientationData.orientation.x;
}