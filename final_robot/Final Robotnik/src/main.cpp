#include <Arduino.h>
// #include "lineFollowing.h"
#include "wallFollowing.h"
#include "pins.h"
#include "motion.h"
// #include "gyro.h"
// #include "ir.h"
#include "tof.h"





void setup() {
    Serial.begin(9600);
    setupPins();
    setupToF();
    // setupGyro();
    // attachInterrupt(digitalPinToInterrupt(ENCODER_R1),check ,RISING);

}
// }

// void loop() {

    // // cheking gyro
    // rotateRobot('L',90);
    // delay(2000);
    // rotateRobot('R',180);
    // delay(2000);
    // while(true);


       

   
// }






  

void loop() {



    runWallFollower();
    delay(10);
    // // cheking gyro
    // rotateRobot('L',90);
    // delay(2000);
    // rotateRobot('R',180);
    // delay(2000);
    // while(true);


//   // Read and print all 6 distances
//   readToF();
//   for (int i = 0; i < 6; i++) {
//     Serial.print(tof_values[i]);
//     Serial.print(" mm    ");
//   }
//   Serial.println();
//   delay(1000);
}

