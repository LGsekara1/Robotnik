// BTS7960 Motor Driver - Dual Motor Test (RR + LL)
// Using: L_PWM, R_PWM for each motor

#define RR_L_PWM 2     // Right motor, Left PWM input
#define RR_R_PWM 3     // Right motor, Right PWM input
#define LL_L_PWM 4     // Left motor, Left PWM input
#define LL_R_PWM 5     // Left motor, Right PWM input

// Defining encoders
#define EncoderRA 18   // Right encoder A (interrupt pin)
#define EncoderRB 23   // Right encoder B
#define EncoderLA 19   // Left encoder A (interrupt pin)
#define EncoderLB 25   // Left encoder B

volatile long posR = 0;
volatile long posL = 0;

float k = 1.0;     // correction gain
int speedPWM = 0;  // current PWM
int delta = 0;     // correction term

// ======================================================
// Setup
// ======================================================
void setup() {
  // Motor pins
  pinMode(RR_L_PWM, OUTPUT);
  pinMode(RR_R_PWM, OUTPUT);
  pinMode(LL_L_PWM, OUTPUT);
  pinMode(LL_R_PWM, OUTPUT);

  // Encoder pins
  pinMode(EncoderRA, INPUT);
  pinMode(EncoderRB, INPUT);
  pinMode(EncoderLA, INPUT);
  pinMode(EncoderLB, INPUT);

  Serial.begin(115200);
  Serial.println("BTS7960 Dual Motor Test Starting...");

  // Attach interrupts on encoder A channels
  attachInterrupt(digitalPinToInterrupt(EncoderRA), readEncoderR, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderLA), readEncoderL, RISING);
}

// ======================================================
// Drive both motors forward/reverse with PWM
// ======================================================
void driveMotors(int pwm, bool forward) {
  int pwmR = constrain(pwm - delta, 0, 255);
  int pwmL = constrain(pwm + delta, 0, 255);

  if (forward) {
    // Forward
    analogWrite(RR_R_PWM, pwmR);
    analogWrite(RR_L_PWM, 0);
    analogWrite(LL_R_PWM, pwmL);
    analogWrite(LL_L_PWM, 0);
  } else {
    // Reverse
    analogWrite(RR_R_PWM, 0);
    analogWrite(RR_L_PWM, pwmL);
    analogWrite(LL_R_PWM, 0);
    analogWrite(LL_L_PWM, pwmR);
  }
}

// ======================================================
// Main loop
// ======================================================
void loop() {
  // ---- Ramp up forward ----
  for (speedPWM = 0; speedPWM <= 255; speedPWM += 1) {
    delta = (int)(k * (posL - posR));
    driveMotors(speedPWM, true);

    Serial.print("R: "); Serial.print(posR);
    Serial.print("  L: "); Serial.println(posL);

    delay(10);
  }
  delay(1000);

  // ---- Ramp down forward ----
  for (speedPWM = 255; speedPWM >= 0; speedPWM -= 1) {
    delta = (int)(k * (posL - posR));
    driveMotors(speedPWM, true);

    Serial.print("R: "); Serial.print(posR);
    Serial.print("  L: "); Serial.println(posL);

    delay(10);
  }
  delay(1000);

  // ---- Ramp up reverse ----
  for (speedPWM = 0; speedPWM <= 255; speedPWM += 1) {
    delta = (int)(k * (posL - posR));
    driveMotors(speedPWM, false);

    Serial.print("R: "); Serial.print(posR);
    Serial.print("  L: "); Serial.println(posL);

    delay(10);
  }
  delay(1000);

  // ---- Ramp down reverse ----
  for (speedPWM = 255; speedPWM >= 0; speedPWM -= 1) {
    delta = (int)(k * (posL - posR));
    driveMotors(speedPWM, false);

    Serial.print("R: "); Serial.print(posR);
    Serial.print("  L: "); Serial.println(posL);

    delay(10);
  }
  delay(2000);
}

// ======================================================
// Encoder ISRs
// ======================================================
void readEncoderR() {
  // Direction based on B channel
  if (digitalRead(EncoderRB)) posR++;
  else posR--;
}

void readEncoderL() {
  // Direction based on B channel
  if (digitalRead(EncoderLB)) posL--;
  else posL++;
}
