#include "Oled.h"

Screens screen;

void Display::beginOled()
{
    beginS();
    
}

void Display::handleOled()
{
    // read the state of the switch into a local variable
    uint8_t reading = digitalRead(BUTTON_PIN);
      // Change screen when the pushbutton is pressed

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
