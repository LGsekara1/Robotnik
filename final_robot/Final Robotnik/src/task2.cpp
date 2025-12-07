#include "task2.h"
#include "lineFollowing.h"
#include "ir.h"
#include "motion.h"
#include "encoder.h"
#include"gyro.h"



void ramp(){
    // readGyro();
    updateGyro();
    if (abs(currentPitch)<5)startMotors(70,70);
    else if(currentPitch>5)startMotors(120,120);
    else if(currentPitch<-5)startMotors(50,50);
}


bool ifInArray(int arr[], int size, int element) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == element) return true;
    }
    return false;
}

void Task2(){
    // char arrow_direction[10] = {'R', 'R', 'R', 'L', 'L', 'L', 'R', 'R', 'R', 'R'};
    // int arrow_angle[10] = {0, 90, 30, 120, 15, 70, 40, 80, 50, 15};
    int dashArray[5]={7, 8, 9, 13, 14};
    int dashCount=0;

    while(true){
        runLineFollower(50,50);
        // readIR();
        if (dashCount==14 && allZeros(ir_values,8)==1){stopMotors();break;}
        if (allOnes(ir_values,8)==1){
            if (ifInArray(dashArray,5,dashCount))startMotors(-10,120);
            else startMotors(50,50);
            // startMotors(50,50);
            while(true){
                readIR();
                if (isNextNode()){
                    //  goDistance(10,70);
                    // turnUntilLine('L');
                    dashCount++;
                    break;}
            }
        }
    }
}




// void Task2Mod(){
//     // char arrow_direction[10] = {'R', 'R', 'R', 'L', 'L', 'L', 'R', 'R', 'R', 'R'};
//     // int arrow_angle[10] = {0, 90, 30, 120, 15, 70, 40, 80, 50, 15};
//     int dashArray[5]={7, 8, 9, 13, 14};
//     int dashCount=0;

//     while(true){
//         runLineFollower(50,50);
//         // readIR();
//         if (dashCount==14 && allZeros(ir_values,8)==1){stopMotors();break;}
//         if (allOnes(ir_values,8)==1){
//             if (ifInArray(dashArray,5,dashCount))startMotors(-10,120);
//             // else startMotors(50,50);
//             // startMotors(50,50);
//             while(true){
//                 readIR();
//                 if (isNextNode()){
//                      goDistance(10,50);
//                     turnUntilLine('L');
//                     dashCount++;
//                     break;}
//             }
//         }

//     }

// }





void Task2Mo2(){
        // char arrow_direction[10] = {'R', 'R', 'R', 'L', 'L', 'L', 'R', 'R', 'R', 'R'};
    // int arrow_angle[10] = {0, 90, 30, 120, 15, 70, 40, 80, 50, 15};
    // int dashArray[5]={7, 8, 9, 13, 14};
    // int dashCount=0;

    while(true){
        runLineFollower(50,50);
        // readIR();
        // if (dashCount==14 && allZeros(ir_values,8)==1){stopMotors();break;}
        if (allZeros(ir_values,8)==1){stopMotors();delay(500);break;}
        if (allOnes(ir_values,8)==1){
            // if (ifInArray(dashArray,5,dashCount))startMotors(-10,120);
            // else startMotors(50,50);
            // startMotors(50,50);
            resetPulses();
            while(true){
                readIR();
                if (isNextNode()){
                    //  goDistance(10,50);
                    // turnUntilLine('L');
                    // dashCount++;
                    break;}
                if (distance()>120){
                    goDistance(-100,50);rotateRobot('L',15);resetPulses();startMotors(50,50);
                }
            }
        }
    }



    goDistance(450,100);delay(1000);
    goDistance(-300,70);delay(1000);
    rotateRobot('R',90);


    // right side of the left side one


    goDistance(-150,70);
    rotateRobot('R',90);

    int countAfterRamp=0;
    int lineStatus=0;
    while(true){
        ramp();
        readIR();
        if (isJunction() and lineStatus==0){countAfterRamp++;lineStatus=1;}
        if (allOnes(ir_values,8))lineStatus=0;
        if (countAfterRamp==2){stopMotors();break;}
    }
    delay(500);


}
