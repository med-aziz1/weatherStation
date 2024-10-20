#include "./Oled/Oled.h"

Display disp;
void setup()
{
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  disp.beginOled();
  Serial.begin(9600);
  disp.displayTime();
}
void loop()
{
  disp.handleOled();
  disp.handle();
}