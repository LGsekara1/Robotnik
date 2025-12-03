#include "display.h"


Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
bool display_ok = false;


void setupDisplay() {
  display_ok = display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);
  if (display_ok) {
    display.clearDisplay();
    display.setTextColor(WHITE);
  }
}


void showDisplay(String text, int textSize,int x=0,int y=0) {
  if (!display_ok) return;
  
  display.setTextSize(textSize);
  display.setCursor(x,y);
  display.println(text);
  display.display();
}


void clearDisplay() {
  if (!display_ok) return;
  display.clearDisplay();
  display.display();
}