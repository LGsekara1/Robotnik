#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1;
VL53L0X sensor2;

// XSHUT pins
#define XSHUT_1 7
#define XSHUT_2 8

void setup() {
  Serial.begin(115200);
  Serial.println("start");

  Wire.begin();


  pinMode(XSHUT_1, OUTPUT);
  pinMode(XSHUT_2, OUTPUT);



  // Step 1: Keep both OFF
  digitalWrite(XSHUT_1, LOW);
  digitalWrite(XSHUT_2, LOW);
  delay(10);


  // Step 2: Start sensor 1 only
  digitalWrite(XSHUT_1, HIGH);
  delay(10);

  if (!sensor1.init()) {

    Serial.println("Sensor 1 not found!");
    while (1)
      ;
  }


  sensor1.setAddress(0x30);  // Assign new I2C address
  Serial.println("Sensor 1 ready at 0x30");

  // Step 3: Start sensor 2 only
  digitalWrite(XSHUT_2, HIGH);
  delay(10);

  if (!sensor2.init()) {
    Serial.println("Sensor 2 not found!");
    while (1)
      ;
  }

  sensor2.setAddress(0x31);  // Assign new I2C address
  Serial.println("Sensor 2 ready at 0x31");
}

void loop() {
  uint16_t d1 = sensor1.readRangeSingleMillimeters();
  uint16_t d2 = sensor2.readRangeSingleMillimeters();

  Serial.print("Sensor1 (0x30): ");
  Serial.print(d1);
  Serial.print(" mm   |   Sensor2 (0x31): ");
  Serial.print(d2);
  Serial.println(" mm");

  delay(100);
}