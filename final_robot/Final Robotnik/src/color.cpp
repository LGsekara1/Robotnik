#include "color.h"
#include "pins.h"


int redMin1 = 14; // Red minimum value
int redMax1 = 92; // Red maximum value
int greenMin1 = 15; // Green minimum value
int greenMax1 = 111; // Green maximum value
int blueMin1 = 13; // Blue minimum value
int blueMax1 = 93; // Blue maximum value

int redMin2 = 15; // Red minimum value
int redMax2 = 100; // Red maximum value
int greenMin2 = 15; // Green minimum value
int greenMax2 = 120; // Green maximum value
int blueMin2 = 15; // Blue minimum value
int blueMax2 = 100; // Blue maximum value


int color=0;


int getRed1()   { digitalWrite(COLOR1_S2,LOW);  digitalWrite(COLOR1_S3,LOW);  return pulseIn(COLOR1_OUT, LOW); }
int getGreen1() { digitalWrite(COLOR1_S2,HIGH); digitalWrite(COLOR1_S3,HIGH); return pulseIn(COLOR1_OUT, LOW); }
int getBlue1()  { digitalWrite(COLOR1_S2,LOW);  digitalWrite(COLOR1_S3,HIGH); return pulseIn(COLOR1_OUT, LOW); }

int getRed2()   { digitalWrite(COLOR2_S2,LOW);  digitalWrite(COLOR2_S3,LOW);  return pulseIn(COLOR2_OUT, LOW); }
int getGreen2() { digitalWrite(COLOR2_S2,HIGH); digitalWrite(COLOR2_S3,HIGH); return pulseIn(COLOR2_OUT, LOW); }
int getBlue2()  { digitalWrite(COLOR2_S2,LOW);  digitalWrite(COLOR2_S3,HIGH); return pulseIn(COLOR2_OUT, LOW); }



void setupColor(){
    digitalWrite(COLOR1_S0,HIGH); digitalWrite(COLOR1_S1,LOW);
    digitalWrite(COLOR2_S0,HIGH); digitalWrite(COLOR2_S1,LOW);
}


void readColor(int color_sensor_number){
    int r, g, b;
    if (color_sensor_number==1){
    r = map(getRed1(),   redMin1, redMax1, 255, 0);
    g = map(getGreen1(), greenMin1, greenMax1, 255, 0);
    b = map(getBlue1(),  blueMin1, blueMax1, 255, 0);
    }

    if (color_sensor_number==2){
    r = map(getRed2(),   redMin2, redMax2, 255, 0);
    g = map(getGreen2(), greenMin2, greenMax2, 255, 0);
    b = map(getBlue2(),  blueMin2, blueMax2, 255, 0);
    }
    r = constrain(r, 0, 255);
    g = constrain(g, 0, 255);
    b = constrain(b, 0, 255);

    if      (r > g && r > b)  {  Serial.print("RED"); color = 1;    }
    else if (g > r && g > b)  {  Serial.print("GREEN"); color = 2;  }
    else if (b > r && b > g)  {  Serial.print("BLUE"); color = 3;   }  
    else                      {  Serial.print("No color"); color = 0; }

}





void calibrateColor(int color_sensor_number){
    int minlist[3];
    int maxlist[3];
    unsigned long t_initial=millis();
    int r,g,b;
    if (color_sensor_number==1){
        r=getRed1(); minlist[0]=r; maxlist[0]=r;
        g=getGreen1(); minlist[1]=g; maxlist[1]=g;
        b=getBlue1(); minlist[2]=b; maxlist[2]=b;
        while ((millis()-t_initial)<5000){
            r=getRed1();
            if (r<minlist[0])minlist[0]=r;
            if (r>maxlist[0])maxlist[0]=r;
            g=getGreen1();
            if (g<minlist[1])minlist[1]=g;
            if (g>maxlist[1])maxlist[1]=g;
            b=getBlue1();
            if (b<minlist[2])minlist[2]=b;
            if (b>maxlist[2])maxlist[2]=b;
        }
    }
    if (color_sensor_number==2){
        r=getRed2(); minlist[0]=r; maxlist[0]=r;
        g=getGreen2(); minlist[1]=g; maxlist[1]=g;
        b=getBlue2(); minlist[2]=b; maxlist[2]=b;
        while ((millis()-t_initial)<5000){
            r=getRed2();
            if (r<minlist[0])minlist[0]=r;
            if (r>maxlist[0])maxlist[0]=r;
            g=getGreen2();
            if (g<minlist[1])minlist[1]=g;
            if (g>maxlist[1])maxlist[1]=g;
            b=getBlue2();
            if (b<minlist[2])minlist[2]=b;
            if (b>maxlist[2])maxlist[2]=b;
        }
    }
    Serial.println("Color Sensor ");Serial.println(color_sensor_number);
    Serial.print("Red Min: ");Serial.print(minlist[0]); Serial.print("  Max: ");Serial.println(maxlist[0]);
    Serial.print("Green Min: ");Serial.print(minlist[1]); Serial.print("  Max: ");Serial.println(maxlist[1]);
    Serial.print("Blue Min: ");Serial.print(minlist[2]); Serial.print("  Max: ");Serial.println(maxlist[2]);
}