#include "wallFollowing.h"
#include "pins.h"   
#include "motion.h"
#include "tof.h"


const float wall_Kp = 0.50; 
const float wall_Kd = 0.0;

int wall_lastError = 0;
int wall_P = 0, wall_I = 0, wall_D = 0;
int wall_PID_value = 0;

const int TARGET_DIST = 100;
const int MIN_DIST = 10;
const int MAX_DIST = 200;

const int WALL_BASE_SPEED = 100;
const int WALL_MIN_SPEED = 0;
const int WALL_MAX_SPEED = 200;



float last_wall_error = 0;

void setMotors2(int leftSpeed, int rightSpeed) {
    analogWrite(L_LPWM, leftSpeed);
    digitalWrite(L_RPWM, LOW);
    analogWrite(R_RPWM, rightSpeed);
    digitalWrite(R_LPWM, LOW);
}

void runWallFollower() {
    readToF();
    int current_distance = tof_values[1];

    current_distance=constrain(current_distance,MIN_DIST,MAX_DIST);
    if (current_distance == 0) return; //current_distance = 140;

    int wall_error = TARGET_DIST - current_distance;
    wall_P = wall_error;
    wall_D = wall_error - last_wall_error;
    wall_PID_value = (wall_Kp * wall_P)  +  (wall_Kd * wall_D);
    last_wall_error = wall_error;
    
    int leftSpeed = WALL_BASE_SPEED + wall_PID_value;
    int rightSpeed = WALL_BASE_SPEED - wall_PID_value;


    leftSpeed = constrain(leftSpeed, WALL_MIN_SPEED, WALL_MAX_SPEED );
    rightSpeed = constrain(rightSpeed, WALL_MIN_SPEED, WALL_MAX_SPEED );

       
    // analogWrite(L_LPWM, leftSpeed);
    // digitalWrite(L_RPWM, LOW);
    // analogWrite(R_RPWM, rightSpeed);
    // digitalWrite(R_LPWM, LOW);
    setMotors2(leftSpeed,rightSpeed);
}