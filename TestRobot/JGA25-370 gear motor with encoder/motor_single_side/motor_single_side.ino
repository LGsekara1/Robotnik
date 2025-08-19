// BTS7960 Motor Driver - Single Motor Test
// Using: L_PWM, R_PWM, L_EN, R_EN

#define L_PWM 10    // Left PWM input (PWM pin)
#define R_PWM 11    // Right PWM input (PWM pin)
#define L_EN 25     // Left enable
#define R_EN 24     // Right enable

int speedPWM = 0;  // 0 - 255

void setup() {
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);

  // Enable both sides
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_EN, HIGH);

  Serial.begin(9600);
  Serial.println("BTS7960 Single Motor Test Starting...");
}

// Drive motor forward or reverse with PWM
void driveMotor(int pwm, bool forward) {
  if (forward) {
    analogWrite(R_PWM, pwm);  // Forward drive
    analogWrite(L_PWM, 0);
  } else {
    analogWrite(R_PWM, 0);
    analogWrite(L_PWM, pwm);  // Reverse drive
  }
}

void loop() {
  // Ramp forward
  for (speedPWM = 0; speedPWM <= 255; speedPWM += 5) {
    driveMotor(speedPWM, true);
    delay(50);
  }

  delay(1000);

  // Ramp down
  for (speedPWM = 255; speedPWM >= 0; speedPWM -= 5) {
    driveMotor(speedPWM, true);
    delay(50);
  }

  delay(1000);

  // Ramp reverse
  for (speedPWM = 0; speedPWM <= 255; speedPWM += 5) {
    driveMotor(speedPWM, false);
    delay(50);
  }

  delay(1000);

  // Ramp down
  for (speedPWM = 255; speedPWM >= 0; speedPWM -= 5) {
    driveMotor(speedPWM, false);
    delay(50);
  }

  delay(2000);
}
