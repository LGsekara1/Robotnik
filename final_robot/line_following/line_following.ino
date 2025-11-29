// ================================================================
// Simple PID Line Follower Robot (Reykha S8 + JGA25-370 Motors)
// ================================================================

// --- 1. CONFIGURATION & PINS ---
// Adjust these constants to match your specific hardware

// JGA25-370 Motor Wiring (For reference):
// Red:    Motor + (Connect to OUT1 / OUT3)
// White:  Motor - (Connect to OUT2 / OUT4)
// Black:  Encoder GND
// Blue:   Encoder VCC (5V)
// Green:  Encoder Phase A (Optional - not used in this simple code)
// Yellow: Encoder Phase B (Optional - not used in this simple code)

// Number of sensors (Updated for Reykha S8)
const int NUM_SENSORS = 8;

// Motor Driver Pins (L298N example)
//const int ENA = 10; // PWM Pin for Left Motor Speed
const int L_LPWM = 9;  // Left Motor Direction
const int L_RPWM = 10;  // Left Motor Direction
const int R_LPWM = 6;  // Right Motor Direction
const int R_RPWM = 7;  // Right Motor Direction
//const int ENB = 5;  // PWM Pin for Right Motor Speed

// Optional: Encoder Pins (Defined here for reference, but not used in loop)
// const int LEFT_ENC_A = 2; 
// const int LEFT_ENC_B = 3;
// const int RIGHT_ENC_A = 18;
// const int RIGHT_ENC_B = 19;

// Sensor Pins (Digital inputs from your array)
// IMPORTANT: Update these to match where you connected your 8 Reykha pins
const int sensorPins[NUM_SENSORS] = {22, 23, 24, 25, 26, 27, 28, 29}; 

// --- 2. PID CONSTANTS (THE TUNING PART) ---
// You must tune these values! Start with Kp, then Kd, then Ki.
float Kp = 25.0; // Proportional (Reaction strength)
float Ki = 0.0;  // Integral (Accumulated error correction)
float Kd = 50.0; // Derivative (Damping/predicting future error)

// Motor Speed Settings
// JGA25-370 motors are powerful. If they are high RPM (e.g. 1000RPM), 
// lower this BASE_SPEED to 100-120. If low RPM (e.g. 300RPM), keep 150-200.
const int BASE_SPEED = 100; // Base speed (0-255)
const int MAX_SPEED = 255;  // Maximum limit

// --- 3. VARIABLES ---
int ir_values[NUM_SENSORS]; // Array of 8 bools (0s and 1s)
int lastError = 0;
int P, I, D;
int PID_value;

void setup() {
  // Initialize Motor Pins
  // pinMode(ENA, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(L_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);
  pinMode(R_RPWM, OUTPUT);
  // pinMode(ENB, OUTPUT);

  // Initialize Sensor Pins
  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  // Start Serial for debugging
  Serial.begin(9600);
}

void loop() {
  // 1. READ SENSORS
  // Reads the 8 pins into the ir_values array
  readSensors();

  // 2. CALCULATE ERROR
  // Calculates position based on the 8 sensor values
  int error = calculateError();
  Serial.println(error);

  // 3. PID CALCULATIONS
  P = error;
  I = I + error;
  D = error - lastError;

  // Compute the PID Output
  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  // Save current error for next loop's 'D' calculation
  lastError = error;

  // 4. MOTOR CONTROL
  calculateMotorSpeeds(PID_value);
}

// ================================================================
// HELPER FUNCTIONS
// ================================================================

// Reads sensor data into the ir_values array
void readSensors() {
  // If you are using a library for Reykha S8, replace this loop 
  // with your library's read function to fill ir_values[0] to [7]
  for (int i = 0; i < NUM_SENSORS; i++) {
    ir_values[i] = digitalRead(sensorPins[i]);
  }
}

// Calculates how far the robot is from the center line
int calculateError() {
  long weightedSum = 0;
  int activeSensors = 0;

  // Weights for 8 sensors:
  // 0: Far Left  (-4)
  // 3: Left Center (-1)
  // 4: Right Center (1)
  // 7: Far Right (4)
  // Center is virtually between index 3 and 4
  int weights[8] = {-4, -3, -2, -1, 1, 2, 3, 4};

  for (int i = 0; i < NUM_SENSORS; i++) {
    if (ir_values[i] == 1) { // Assuming 1 is Line detected
      weightedSum += weights[i];
      activeSensors++;
    }
  }

  // If no line is detected, use the last known error to keep turning
  if (activeSensors == 0) {
    return lastError; 
  }

  // Return the weighted sum as the error
  return weightedSum; 
}

void calculateMotorSpeeds(int correction) {
  // Adjust speeds based on PID correction
  int leftMotorSpeed = BASE_SPEED + correction;
  int rightMotorSpeed = BASE_SPEED - correction;

  // Constrain speeds to 0-255 range so we don't send invalid PWM
  leftMotorSpeed = constrain(leftMotorSpeed, 0, MAX_SPEED);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, MAX_SPEED);

  // Apply to motors
  setMotors(leftMotorSpeed, rightMotorSpeed);
}

void setMotors(int leftSpeed, int rightSpeed) {
  // Left Motor Forward
  analogWrite(L_LPWM, leftSpeed);
  digitalWrite(L_RPWM, LOW);
  // digitalWrite(IN2, LOW);

  // Right Motor Forward
  analogWrite(R_RPWM, rightSpeed);
  digitalWrite(R_LPWM, LOW);
  // digitalWrite(IN4, LOW);
}





// const int L_LPWM=9;
// const int L_RPWM=10;
// const int R_LPWM=6;
// const int R_RPWM=7;

// void setup(){
//   pinMode(L_LPWM,OUTPUT);
//   pinMode(L_RPWM,OUTPUT);
//   pinMode(R_LPWM,OUTPUT);
//   pinMode(R_RPWM,OUTPUT);
//   analogWrite(L_RPWM,0);
//   analogWrite(L_LPWM,100);
//   analogWrite(R_LPWM,0);
//   analogWrite(R_RPWM,100);


// }

// void loop(){
//   // analogWrite(R_RPWM,0);
//   // analogWrite(R_LPWM,100);
//   // delay(10000);
//   // analogWrite(R_RPWM,100);
//   // analogWrite(R_LPWM,0);
//   // delay(1000);
// }

// const int sensorPins[8] = {22, 23, 24, 25, 26, 27, 28, 29}; 
// int ir_values[8];
// void setup(){
//    for (int i = 0; i < 8; i++) {
//     pinMode(sensorPins[i], INPUT);
//    }
//   Serial.begin(9600);

// }
// void loop() {
//   // If you are using a library for Reykha S8, replace this loop 
//   // with your library's read function to fill ir_values[0] to [7]
//   for (int i = 0; i < 8; i++) {
//     ir_values[i] = digitalRead(sensorPins[i]);
//     Serial.print(ir_values[i]);
//   }
//   Serial.println();
//   delay(1000);
// }