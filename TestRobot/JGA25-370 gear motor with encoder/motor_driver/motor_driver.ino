// BTS7960 Motor Driver - Dual Motor Test (RR + LL)
// Using: L_PWM, R_PWM, L_EN, R_EN for each motor

#define RR_L_PWM 8     // Right-Right motor, Left PWM input
#define RR_R_PWM 9     // Right-Right motor, Right PWM input
#define RR_L_EN 23     // Right-Right motor, Left enable
#define RR_R_EN 22     // Right-Right motor, Right enable

#define LL_L_PWM 10    // Left-Left motor, Left PWM input
#define LL_R_PWM 11    // Left-Left motor, Right PWM input
#define LL_L_EN 25     // Left-Left motor, Left enable
#define LL_R_EN 24     // Left-Left motor, Right enable

int speedPWM = 0;  // 0 - 255

void setup() {
  // Set pins as outputs
  pinMode(RR_L_PWM, OUTPUT);
  pinMode(RR_R_PWM, OUTPUT);
  pinMode(RR_L_EN, OUTPUT);
  pinMode(RR_R_EN, OUTPUT);

  pinMode(LL_L_PWM, OUTPUT);
  pinMode(LL_R_PWM, OUTPUT);
  pinMode(LL_L_EN, OUTPUT);
  pinMode(LL_R_EN, OUTPUT);

  // Enable both drivers
  digitalWrite(RR_L_EN, HIGH);
  digitalWrite(RR_R_EN, HIGH);
  digitalWrite(LL_L_EN, HIGH);
  digitalWrite(LL_R_EN, HIGH);

  Serial.begin(9600);
  Serial.println("BTS7960 Dual Motor Test Starting...");
}

// Drive both motors forward/reverse with PWM
void driveMotors(int pwm, bool forward) {
  if (forward) {
    // Forward
    analogWrite(RR_R_PWM, pwm);
    analogWrite(RR_L_PWM, 0);
    analogWrite(LL_R_PWM, pwm);
    analogWrite(LL_L_PWM, 0);
  } else {
    // Reverse
    analogWrite(RR_R_PWM, 0);
    analogWrite(RR_L_PWM, pwm);
    analogWrite(LL_R_PWM, 0);
    analogWrite(LL_L_PWM, pwm);
  }
}

void loop() {
  // Ramp forward
  for (speedPWM = 0; speedPWM <= 255; speedPWM += 5) {
    driveMotors(speedPWM, true);
    delay(50);
  }
  delay(1000);

  // Ramp down forward
  for (speedPWM = 255; speedPWM >= 0; speedPWM -= 5) {
    driveMotors(speedPWM, true);
    delay(50);
  }
  delay(1000);

  // Ramp reverse
  for (speedPWM = 0; speedPWM <= 255; speedPWM += 5) {
    driveMotors(speedPWM, false);
    delay(50);
  }
  delay(1000);

  // Ramp down reverse
  for (speedPWM = 255; speedPWM >= 0; speedPWM -= 5) {
    driveMotors(speedPWM, false);
    delay(50);
  }
  delay(2000);
}
