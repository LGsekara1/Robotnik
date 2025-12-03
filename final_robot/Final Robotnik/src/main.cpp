#include <Arduino.h>
#include <Wire.h> 
#include "lineFollowing.h"
#include "wallFollowing.h"
#include "encoder.h"
#include "pins.h"
#include "motion.h"
#include "gyro.h"
#include "ir.h"
#include "tof.h"
#include "display.h"
#include "armServo.h"














void setup() {
    Wire.begin();
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(ENCODER_R1),changePulses ,RISING);
    setupPins();
    // setupDisplay();clearDisplay();
    // showDisplay("Initializing...",2,0,0);
    Serial.println("Pins and Display Initialized");
    // setupGyro();
    // delay(5000);
    // Serial.println("Gyro Initialized");
    // showDisplay("Gyro Initialized",2,0,30);
    setupToF();
    // showDisplay("ToF Initialized",2,0,30);
    // setupCalibrateIR();
    // Serial.println(gyro_ok);
    Serial.println("Setup Complete");
    // showDisplay("Moda ",3,0,0);
    // showDisplay("Kariya",3,0,30);
    // setupServo();
    initWallFollower();

}








  

void loop() {

    runWallFollowerLinear(100);


}
