#include <Wire.h>
#include <VL53L0X.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

VL53L0X tof[7];

#define BNO_RESET_PIN 35     // connect to nRESET pin on BNO055 breakout
#define BNO_BOOT_PIN 34


Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
void hardResetBNO055() {


  pinMode(BNO_RESET_PIN, OUTPUT);
  pinMode(BNO_BOOT_PIN,OUTPUT);
  digitalWrite(BNO_BOOT_PIN,LOW);
  delay(2000);
  digitalWrite(BNO_BOOT_PIN,HIGH);
  
  digitalWrite(BNO_RESET_PIN, LOW);   // hold reset
  delay(10);                          // minimum 1 ms; 10–20 ms recommended
  digitalWrite(BNO_RESET_PIN, HIGH);  // release reset


  delay(700);                         // **mandatory boot time**
 }

// // OLED
// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// XSHUT pins
int xshutPins[7] = {39,40,41,42,43,44,45};
//int xshutPins[6] = {39,40,41,42,43,44};
// New I2C addresses
uint8_t tofAddr[7] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36};
//uint8_t tofAddr[6] = {0x30,0x31,0x32,0x33,0x34,0x35};


void setup() {
  Serial.begin(115200);
  Serial.println("pakaya");
  Wire.begin();
  hardResetBNO055();
 

  
  
//igitalWrite(BNO_RESET_PIN, HIGH);  // idle state
    for(int i=0; i<7; i++){
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }
  delay(50);

  


  // Perform a clean hard reset before initialization
  
  
Serial.println("pakaya2");
  //Now start library init
  if (!bno.begin()) {
    Serial.println("BNO055 not detected!");
    while (1);
  }

  delay(1000);  // give sensor time to enter NDOF or desired mode
  bno.setExtCrystalUse(true);

  Serial.println("BNO055 initialized after hard reset.");


    //Init BNO055


  // --- OLED INIT ---
  // if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  //   Serial.println("OLED not found!");

  // }

  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(SSD1306_WHITE);


  //Turn off all ToF sensors

  // Init ToF one by one
  for(int i=0; i<7; i++){
    digitalWrite(xshutPins[i], HIGH);
    
    delay(10);

    tof[i].init();
    tof[i].setAddress(tofAddr[i]);
    
    Serial.print("ToF "); Serial.print(i);
    Serial.print(" set to 0x");
    Serial.println(tofAddr[i], HEX);
  }



  Serial.println("System ready");
}

void loop() {

  // // --- Display ToF 0 reading ---
  float d1 = tof[0].readRangeSingleMillimeters();
  delay(50);
  float d2 = tof[1].readRangeSingleMillimeters();
  delay(50);
  float d3 = tof[2].readRangeSingleMillimeters();
  delay(50);
  float d4 = tof[3].readRangeSingleMillimeters();
  delay(50);
  float d5 = tof[4].readRangeSingleMillimeters();
  delay(50);
  float d6 = tof[5].readRangeSingleMillimeters();
  delay(50);
  float d7 = tof[6].readRangeSingleMillimeters();
  
  float D[7] = {d1,d2,d3,d4,d5,d6,d7};

for (int i=0;i<7;i++){
  Serial.print(D[i]);
  Serial.println("|");
}
 sensors_event_t event;
  bno.getEvent(&event);

  Serial.print("Orientation X: ");
  Serial.print(event.orientation.x);
  Serial.print(" Y: ");
  Serial.print(event.orientation.y);
  Serial.print(" Z: ");
  Serial.println(event.orientation.z);


}
