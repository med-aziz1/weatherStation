#pragma once
#include "Screens/Screen.h"
#include "./Config/Config.h"
class Display : public Screens
{
public:
    void beginOled();
    void handleOled();
    void end();
    void updateScreen();
    uint8_t displayScreenNumMax = 4;
    uint8_t buttonState;           // current reading from the input pin
    uint8_t lastButtonState = LOW; // previous reading from the input pin

    unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
    unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers
    unsigned long lastTimer = 0;
    unsigned long timerDelay = 15000;
    int lastMillis = 0;
};
extern Display disp;