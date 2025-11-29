#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define width 128
#define height 64



Adafruit_SSD1306 display(width, height, &Wire);

void setup() {
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
  
}
