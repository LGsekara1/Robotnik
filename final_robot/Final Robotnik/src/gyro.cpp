

#include "gyro.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <Wire.h>

// --- CONFIGURATION ---
const int INTERRUPT_PIN = 2; 

MPU6050 mpu; // Address 0x68

// --- VARIABLES ---
bool gyro_ok = false;
uint8_t fifoBuffer[64]; 
Quaternion q;           
float ypr[3];           

// Global storage
float currentYaw = 0.0; 
float currentPitch = 0.0;

volatile bool mpuInterrupt = false;     
void dmpDataReady() {
    mpuInterrupt = true;
}

// Helper to wrap angle to 0-360
float wrap360(float angleDeg) {
    while (angleDeg < 0.0) angleDeg += 360.0;
    while (angleDeg >= 360.0) angleDeg -= 360.0;
    return angleDeg;
}

void setupGyro() {
    Serial.println(F("Initializing MPU6050..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    if (!mpu.testConnection()) {
        Serial.println(F("MPU connection FAILED"));
        gyro_ok = false;
        return; 
    }

    // Initialize DMP
    uint8_t devStatus = mpu.dmpInitialize();

    // YOUR OFFSETS (Keep these!)
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); 

    if (devStatus == 0) {
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.setDMPEnabled(true);
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        gyro_ok = true;
        Serial.println(F("DMP Ready!"));
    } else {
        Serial.print(F("DMP Failed code: "));
        Serial.println(devStatus);
        gyro_ok = false;
    }
}

// Returns TRUE if we successfully updated currentYaw
// Returns FALSE if the FIFO was empty or corrupt
bool updateGyro() {
    if (!gyro_ok) return false;

    // Check if data is available (Non-blocking)
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
        
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        VectorFloat gravity;
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        
        // Convert to degrees
        float yawDeg   = ypr[0] * 180.0 / M_PI;
        float pitchDeg = ypr[1] * 180.0 / M_PI;
        
        currentYaw = wrap360(yawDeg);
        currentPitch = pitchDeg;
        
        return true; // SUCCESS! New data.
    }
    
    return false; // NO DATA. Use old value.
}

void flushGyro() {
    if (!gyro_ok) return;
    // Read continuously until buffer is drained
    // This removes "lag" from old packets
    for (int i = 0; i < 10; i++) {
        updateGyro();
        delay(5);
    }
}











// #include "gyro.h"
// #include "display.h"

// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BNO055.h>

// // IMU
// Adafruit_BNO055 bno=Adafruit_BNO055(55, 0x28, &Wire);
// // Adafruit_BNO055 bno;
// bool gyro_ok = false;

// void gyro_error_indicator(){                             //error detection
//   // showDisplay("Error:",2,0,0);
//   // showDisplay("Gyro",2,0,30);
//   for (int i=0;i<5;i++){
//     digitalWrite(13,HIGH);
//     delay(500);
//     digitalWrite(13,LOW);
//     delay(500);
//   }
// }

// void setupGyro() {
//   gyro_ok = bno.begin();
//   delay(1000);
//   if (gyro_ok) {
//     bno.setExtCrystalUse(true);
//     flushGyro();
//   }
//   else {gyro_error_indicator();}
// }

// float readGyro() {
//   // if (!imu_ok) return 0;
//   sensors_event_t orientationData;
//   bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
//   return orientationData.orientation.x;
// }

// void flushGyro() {
//   for (int i = 0; i < 5; i++) {
//     readGyro();delay(10);
//   }
// }







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