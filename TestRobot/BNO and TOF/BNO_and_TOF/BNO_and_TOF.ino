#include <Wire.h>
#include <Adafruit_BNO055.h>

#define BNO_BOOT_PIN 34
#define BNO_RESET_PIN 35

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void hardResetBNO055() {
  digitalWrite(BNO_RESET_PIN, LOW);
  delay(10);
  digitalWrite(BNO_RESET_PIN, HIGH);
  delay(700);
}

void setup() {
  Serial.begin(115200);

  // 1. Hold BOOT low during reset
  pinMode(BNO_BOOT_PIN, OUTPUT);
  digitalWrite(BNO_BOOT_PIN,LOW);
  delay(2000);
  pinMode(BNO_BOOT_PIN, INPUT);

  // 2. Setup reset
  pinMode(BNO_RESET_PIN, OUTPUT);
  
  digitalWrite(BNO_RESET_PIN, HIGH);

  // 3. Hard reset
  hardResetBNO055();

  // 4. Release BOOT pin to high impedance (optional)
  

  // 5. Initialize sensor
  if (!bno.begin()) {
    Serial.println("BNO055 not detected!");
    while (1);
  }

  delay(1000);
  bno.setExtCrystalUse(true);

  Serial.println("BNO055 initialized.");
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);

  Serial.print("Orientation X: ");
  Serial.print(event.orientation.x);
  Serial.print(" Y: ");
  Serial.print(event.orientation.y);
  Serial.print(" Z: ");
  Serial.println(event.orientation.z);

  delay(100);
}
