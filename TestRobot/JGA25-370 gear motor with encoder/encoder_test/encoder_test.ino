#define ENCA 2
#define ENCB 3

volatile long encoderPos = 0; // Position counter

void setup() {
  Serial.begin(115200);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);

  // Use interrupts for better accuracy
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, CHANGE);
}

void loop() {
  Serial.println(encoderPos);
  delay(50);
}

void readEncoder() {
  int a = digitalRead(ENCA);
  int b = digitalRead(ENCB);

  if (a == b) {
    encoderPos++; // CW
  } else {
    encoderPos--; // CCW
  }
}
