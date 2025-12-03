#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>


#define width 128
#define height 64

#define ENCA 2    // interrupt pin on Mega
#define ENCB 3    // normal digital pin

Adafruit_SSD1306 display(width, height, &Wire);

volatile long encoderPos = 0;

void readEncoder() {
  int a = digitalRead(ENCA);
  int b = digitalRead(ENCB);

  if (a==1){
    if(b==0){
      encoderPos++;
    }else{
      encoderPos--;
    }
  }
  


}

void setup() {
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, CHANGE);

  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Robotnik");
  display.display();
  delay(1000);
}

void loop() {
  noInterrupts();
  long pos = encoderPos;
  interrupts();

  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println(pos);
  display.display();

  delay(50);
}




