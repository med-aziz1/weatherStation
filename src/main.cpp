#include "./Oled/Oled.h"

Display disp;
int button_state;       // the current state of button
int last_button_state;  // the previous state of button
void setup()
{
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(LED_BUILTIN,OUTPUT);
  disp.beginOled();
  Serial.begin(9600);
  disp.displayTime();
  button_state = digitalRead(BUTTON_PIN);
}
void loop()
{
  last_button_state = button_state;      // save the last state
  button_state = digitalRead(BUTTON_PIN); // read new state
  if (last_button_state == HIGH && button_state == LOW){
    disp.updateScreen();
  }
  disp.handleOled();
  disp.handle();
}