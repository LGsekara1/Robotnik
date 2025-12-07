#include "task4.h"
#include "lineFollowing.h"
#include "wallFollowing.h"
#include "motion.h"
#include "encoder.h"
#include "gyro.h"
#include "tof.h"
#include "ir.h"
#include "color.h"
#include "armServo.h"

void Task4(int color=1,int finalCount=2){
    goDistance(120,70);delay(100);
    rotateRobot('R',90);delay(100);
    goDistance(250,70);delay(100);
    rotateRobot('L',90);delay(100);
    updateGyro();
    float initialYaw=currentYaw;
    float finalYaw=initialYaw+180; if(finalYaw>360)finalYaw-=360;

    // startMotors(70,70);
    // while(abs(currentYaw-finalYaw)>10){
    //     runWallFollowerLinear(100,70);
    //     updateGyro();
    // }
    // runWallFollowerLinear(100,70);delay(100);

    // while(true){
    //     runWallFollowerLinear(100,70);delay(10);
    // }
    // stopMotors();

    readToF();
    float t1=millis();
    while(tof_values[6]<500 || millis()-t1<(2000)){
        runWallFollowerLinear(100,70);
    }
    // startMotors(115,25);

    // updateGyro();
    // while(abs(finalYaw-currentYaw)>5){
    //     updateGyro();
    // }
    // while(tof_values[6]<400){
    //     readToF();
    // }
    // // startMotors(115,25);

    goDistance(100,70);delay(500);
    rotateRobot('R',90);delay(500);
    goDistance(400);delay(500);
    rotateRobot('R',60);delay(500);
    // goDistance(150,70);
    // stopMotors();





    // rotateRobot('R',90);
    // goDistance(200);
    // rotateRobot('R',90);
    // runWallFollowerInner();
    runBallPicker();
    int ballCount;
    readToF();
    float t2=millis();
    while(tof_values[6]<500 || (millis()-t2)<3000 ){
        runWallFollowerInner(100,70,80,5,15,20);
        if (readColor(2)==color and ballCount<finalCount){stopMotors(); pickBall();ballCount++;}
    }

    goDistance(100,70);
    // rotateRobot('R',90);
    // goDistance(200);
    // rotateRobot('R',90);


    goDistance(100,70);delay(500);
    rotateRobot('R',90);delay(500);
    goDistance(400);delay(500);
    rotateRobot('R',60);delay(500);


    while(!isWhiteLine()){
        runWallFollowerLinear(100,70);
    }
    goDistance(120,70);
    rotateRobot('L',90);

    while(!isWhiteLine()){
        runLineFollower(70,70);
    }
    goDistance(120,70);
    rotateRobot('R',90);
}