#include "lineFollowing.h"
#include "pins.h"
#include "ir.h"
#include "motion.h"



// PID Constants
const float line_Kp = 30.0;
const float line_Ki = 0.0;
const float line_Kd = 5;

int line_lastError = 0;
int line_P = 0, line_I = 0, line_D = 0;
int line_PID_value = 0;


// Motor Speed Settings
const int LINE_BASE_SPEED = 100; //PWM(0-255)
const int LINE_MAX_SPEED = 200;
const int LINE_MIN_SPEED = 0;




void setMotors(int leftSpeed, int rightSpeed) {
    analogWrite(L_LPWM, leftSpeed);
    digitalWrite(L_RPWM, LOW);
    analogWrite(R_RPWM, rightSpeed);
    digitalWrite(R_LPWM, LOW);
}


int calculateError() {
    long weightedSum = 0;
    int activeSensors = 0;
    int weights[8] = {-4, -3, -2, -1, 1, 2, 3, 4};

    for (int i = 0; i < NUM_IR_SENSORS; i++) {
        if (ir_values[i] == 1) {
            weightedSum += weights[i];
            activeSensors++;
        }
    }

    if (activeSensors == 0) {
        return line_lastError;
    }

    return weightedSum;
}



void calculateMotorSpeeds(int correction) {
    int leftMotorSpeed = LINE_BASE_SPEED + correction;
    int rightMotorSpeed = LINE_BASE_SPEED - correction;

    leftMotorSpeed = constrain(leftMotorSpeed, LINE_MIN_SPEED, LINE_MAX_SPEED);
    rightMotorSpeed = constrain(rightMotorSpeed, LINE_MIN_SPEED, LINE_MAX_SPEED);

    setMotors(leftMotorSpeed, rightMotorSpeed);
}






void runLineFollower() {
    readIR();
    int line_error = calculateError();
    // Serial.println(error);

    line_P = line_error;
    line_I = line_I + line_error;
    line_D = line_error - line_lastError;
    line_PID_value = (line_Kp * line_P) + (line_Ki * line_I) + (line_Kd * line_D);
    line_lastError = line_error;
    calculateMotorSpeeds(line_PID_value);
}