#include "armServo.h"
#include "pins.h"
#include "motion.h"
#include "sharpIr.h"
#include "encoder.h"
#include "lineFollowing.h"
// #include <Arduino.h>
#include <Servo.h>

Servo boxVertical;     // 100 - 15
Servo boxHorizontal;   // 142 - 100
Servo ballVertical;    // 0 - 180
Servo ballHorizontal;  // 0 -180
Servo ballCylinder;    // 0 - 160

int boxVerticalStatus=0;      //0-up  1-down
int boxHorizontalStatus=0;    //0-closed  1-open
int ballVerticalStatus=0;     //0-up 1-down
int ballCylinderStatus=0;     //0-in 1-out
int ballHorizontalStatus=0;   //0-in 180-out
int ballHorizontalDiscreteStatus=180;   //0-in 180-out


void setupServo(){
    boxVertical.attach(BOX_SERVO_VERTICAL_PIN);boxVertical.write(75);
    boxHorizontal.attach(BOX_SERVO_HORIZONTAL_PIN);boxHorizontal.write(142);

    ballVertical.attach(BALL_SERVO_VERTICAL_PIN);ballVertical.write(180);
    ballHorizontal.attach(BALL_SERVO_HORIZONTAL_PIN);ballHorizontal.write(180);
    ballCylinder.attach(BALL_SERVO_CYLINDER_PIN);ballCylinder.write(180);
}



//box
void boxVerticalUp(){
    if (boxVerticalStatus==0){return;}
    else{
       for (int i=15;i<=100;i++){
           boxVertical.write(i);
           delay(5);
       }
       boxVerticalStatus=0;
    }
}

void boxVerticalDown(){
    if (boxVerticalStatus==1){return;}
    else{
       for (int i=100;i>=15;i--){
           boxVertical.write(i);
           delay(5);
       }
       boxVerticalStatus=1;
    }
}

void boxHorizontalClose(){
    if (boxHorizontalStatus==0){return;}
    else{
       for (int i=100;i<=142;i++){
           boxHorizontal.write(i);
           delay(5);
       }
       boxHorizontalStatus=0;
    }
}

void boxHorizontalOpen(){
    if (boxHorizontalStatus==1){return;}
    else{
       for (int i=142;i>=100;i--){
           boxHorizontal.write(i);
           delay(5);
       }
       boxHorizontalStatus=1;
    }
}

void getBox(){boxHorizontalOpen();boxVerticalDown();boxHorizontalClose();}

void grabBox(){
    resetPulses();
    while(distance()<250)runLineFollower(50,50);
    boxHorizontalOpen();boxVerticalDown();
    goDistance(-300,50);
    boxHorizontalClose();
    goDistance(50,50);
}

void releaseBox(){boxVerticalUp();}








// ball
void ballVerticalUp(){
    if (ballVerticalStatus==0){return;}
    else{
       for (int i=0;i<=0;i++){
           ballVertical.write(i);
           delay(10);
       }
       ballVerticalStatus=0;
    }
}


void ballVerticalDown(){
    if (ballVerticalStatus==1){return;}
    else{
       for (int i=180;i>=0;i--){
           ballVertical.write(i);
           delay(10);
       }
       ballVerticalStatus=1;
    }
}



void ballCylinderIn(){
    if (ballCylinderStatus==0){return;}
    else{
       for (int i=0;i<=180;i++){
           ballCylinder.write(i);
           delay(5);
       }
       ballCylinderStatus=0;
    }
}

void ballCylinderOut(){
    if (ballCylinderStatus==1){return;}
    else{
       for (int i=180;i>=0;i--){
           ballCylinder.write(i);
           delay(5);
       }
       ballCylinderStatus=1;
    }
}


void ballHorizontalIn(){
    if (ballHorizontalStatus==0){return;}
    else{
       for (int i=0;i<=180;i++){
           ballHorizontal.write(i);
           delay(5);
       }
       ballHorizontalStatus=0;
    }
}


void ballHorizontalOut(){
    if (ballHorizontalStatus==1){return;}
    else{
       for (int i=180;i>=0;i--){
           ballHorizontal.write(i);
           delay(5);
       }
       ballHorizontalStatus=1;
    }
}