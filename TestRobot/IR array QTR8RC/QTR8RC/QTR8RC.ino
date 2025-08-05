#include <QTRSensors.h>

//––– Configuration ––––––––––––––––––––––––––––––––––––––––––––––––––––  
const uint8_t sensorPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const uint8_t SensorCount   = sizeof(sensorPins) / sizeof(sensorPins[0]);
QTRSensors qtr;             // single object for both RC & analog types
uint16_t sensorValues[SensorCount];

//––––– Setup –––––––––––––––––––––––––––––––––––––––––––––––––––––––––  
void setup() {
  Serial.begin(9600);
  delay(500);

  // Tell the library we have RC‐type sensors:
  qtr.setTypeRC();
  // Which pins, how many:
  qtr.setSensorPins(sensorPins, SensorCount);
  // Timeout (µs) for very dark surfaces that never discharge:
  qtr.setTimeout(2500);
  // We’re not driving LEDON/IR pin, so leave them always on:
  qtr.setEmitterPin(10);

  //––– Calibrate: fill min/max arrays so read() returns 0–1000 –––  
  digitalWrite(LED_BUILTIN, HIGH);  // indicator during calibration
  for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();                // read & update cal min/max
    delay(20);
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Calibration complete!");
}

//––––– Main Loop ––––––––––––––––––––––––––––––––––––––––––––––––––––  
void loop() {
  // Read all sensors into sensorValues[] (0 = white, 1000 = black)
  qtr.read(sensorValues);

  // Print them out
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(sensorValues[i]);
    if (i + 1 < SensorCount) Serial.print('\t');
  }
  Serial.println();

  delay(200);
}
