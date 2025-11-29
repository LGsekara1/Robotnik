#include "motion.h"
#include "pins.h"
#include "gyro.h"
#include "ir.h"
#include "lineFollowing.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// Motor pins
// const int L_LPWM = 9;
// const int L_RPWM = 10;
// const int R_LPWM = 6;
// const int R_RPWM = 7;

// // IMU
// Adafruit_BNO055 bno=Adafruit_BNO055(55, 0x29, &Wire);
// // Adafruit_BNO055 bno;
// bool imu_ok = false;

// void initIMU() {
//   imu_ok = bno.begin();
//   delay(1000);
//   if (imu_ok) {
//     bno.setExtCrystalUse(true);
//   }
// }

// float getYaw() {
//   // if (!imu_ok) return 0;
//   sensors_event_t orientationData;
//   bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
//   return orientationData.orientation.x;
// }


void setRotation(char direction, int speed = 180) {
  if (direction == 'L') {
    analogWrite(L_LPWM, 0);
    analogWrite(L_RPWM, speed);
    analogWrite(R_LPWM, 0);
    analogWrite(R_RPWM, speed);
  } else if (direction == 'R') {
    analogWrite(L_LPWM, speed);
    analogWrite(L_RPWM, 0);
    analogWrite(R_LPWM, speed);
    analogWrite(R_RPWM, 0);
  }
}




void startMotors(int leftSpeed,int rightSpeed){
  int l=abs(leftSpeed);
  int r=abs(rightSpeed);
  if (leftSpeed>0){analogWrite(L_LPWM, l);analogWrite(L_RPWM, 0);}
  else if(leftSpeed<0){analogWrite(L_LPWM, 0);analogWrite(L_RPWM, l);}
  if (rightSpeed>0){analogWrite(R_LPWM, 0);analogWrite(R_RPWM, r);}
  else if(rightSpeed<0){analogWrite(R_LPWM, r);analogWrite(R_RPWM, 0);}
}

void stopMotors() {
  analogWrite(L_LPWM, 0);
  analogWrite(L_RPWM, 0);
  analogWrite(R_LPWM, 0);
  analogWrite(R_RPWM, 0);
}


void rotateRobot(char direction, float target_angle) {
  if (!imu_ok){
    int t_90=600;
    setRotation(direction);
    delay(t_90/90*target_angle);
    stopMotors();
  }
  else{
  float initial_x = readGyro();
  setRotation(direction);
  while (true) {
    float current_x = readGyro();
    float angle_turned;
    
    if (direction == 'L') {
      angle_turned = initial_x - current_x;
      if (angle_turned < 0) angle_turned += 360;
    } else if (direction == 'R') {
      angle_turned = current_x - initial_x;
      if (angle_turned < 0) angle_turned += 360;
    }
    
    if (angle_turned >= target_angle) {
      stopMotors();
      break;
    }
    delay(10); // Small delay to prevent overwhelming the IMU
  }}
}






int pulses=0;

void check(){
  if (digitalRead(ENCODER_R2) == LOW) {
    pulses++;
  } else {
    pulses--;
  }
}


int ENCODER_COUNT=224;
float CIR=PI*6.5; //cm

void goDistance(float distance){
    float rotations=abs(distance)/CIR;
    float target_pulses=rotations*(float)ENCODER_COUNT;
    pulses=0;
    if (distance>0)startMotors(100,100);
    else if (distance<0)startMotors(-100,-100);
    while(true){
        Serial.println(pulses);
        if (abs(pulses)>target_pulses){stopMotors();return;}
        delay(10);
    }
}


void nodeTraversal(){
    while(true){
        runLineFollower();
        // readIR();
        
        bool isLeft=true;
        bool isRight=true;
        for(int i=0;i<5;i++){
            if (ir_values[i]==0){isLeft=false;break;}
        }
        for(int i=3;i<8;i++){
            if (ir_values[i]==0){isRight=false;break;}
        }
        if (isRight or isLeft){
            stopMotors();
            delay(100);
            goDistance(5);
            delay(100);
            return;
        }
    }
}