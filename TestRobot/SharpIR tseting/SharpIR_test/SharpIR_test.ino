//Library testing
#include <SharpIR.h>


SharpIR sensor2(SharpIR::GP2Y0A41SK0F, A0);

//අමුවෙන් testing
#define sensor A1


void setup(){
  Serial.begin(9600);

}

void loop(){
  float distance1 = sensor.getDistance();
  Serial.println(distance1);
  delay(1000);


  float volts = analogRead(sensor2)*0.0048828125;
  int distance2 = 13*pow(volts,-1);
  delay(1000);

  if (distance2 <=30){
    Serial.println(distance2);
  }




}