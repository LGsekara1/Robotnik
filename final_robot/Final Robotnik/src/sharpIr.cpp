#include "sharpIr.h"
#include "pins.h"

float readSharpIR() {
  long sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += analogRead(SHARP_IR_PIN);   // ← pin is automatically set as INPUT
    delay(2);
  }
  float voltage = sum * (5.0 / 1023.0) / 5.0;
  float distance = 4.443 * pow(voltage, -1.005);

  if (voltage < 0.28 || voltage > 2.8) return 99.0;
  if (distance < 2.0)  distance = 20;
  if (distance > 15.0) distance = 150;

  return distance;
}