//අමුවෙන් testing
// #define sensor A0

// void setup() {
//   Serial.begin(9600);

// }

// void loop() {
//   float sensorValue = analogRead(sensor);
//   Serial.println(sensorValue);
//   delay(500);
// }


//Library testing
#include <SharpIR.h>


SharpIR sensor(SharpIR::GP2Y0A41SK0F, A0);


void setup(){
  Serial.begin(9600);

}

void loop(){
  float distance = sensor.getDistance();
  Serial.println(distance);
  delay(1000);
}