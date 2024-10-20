#include "Oled.h"

Screens screen;

void Display::beginOled()
{
    beginS();
}

void Display::handleOled()
{
    // read the state of the switch into a local variable
    // uint8_t reading = digitalRead(BUTTON_PIN);
    if(digitalRead(BUTTON_PIN) == LOW){
        updateScreen();
    }
//       // Change screen when the pushbutton is pressed
//   if (reading != lastButtonState) {
//     lastDebounceTime = millis();
//   }
//     if ((millis() - lastDebounceTime) > debounceDelay) {
//     if (reading != buttonState) {
//       buttonState = reading;
//       if (buttonState == HIGH) {
//         updateScreen();
//         Serial.println(displayScreenNum);
//         if(displayScreenNum < displayScreenNumMax) {
//           displayScreenNum++;
//         }
//         else {
//           displayScreenNum = 0;
//         }
//         lastTimer = millis();
//       }
//     }
//   }
//   lastButtonState = reading;
//     // Change screen every 15 seconds (timerDelay variable)
//   if ((millis() - lastTimer) > timerDelay) {
//     updateScreen();
//     Serial.println(displayScreenNum);
//     if(displayScreenNum < displayScreenNumMax) {
//       displayScreenNum++;
//     }
//     else {
//       displayScreenNum = 0;
//     }
//     lastTimer = millis();
//   }
}


void Display::updateScreen()
{
    displayScreenNum++;
    if (displayScreenNum == 0)
    {
        displayTime();
    }
    else if (displayScreenNum == 1)
    {
        displayTemperature();
    }
    else if (displayScreenNum == 2)
    {
        displayHumidity();
    }
}
