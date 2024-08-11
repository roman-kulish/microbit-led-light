#include "Button.h"

void Button::processButton()
{
    const uint32_t timeNow = millis();
    if (timeNow - lastDebounceTime < debounceDelay)
    {
        return;
    }

    bool currentState = (digitalRead(pin) == LOW);

    if (currentState && !previousButtonState)
    {
        onPress();
    }

    lastDebounceTime = timeNow;
    previousButtonState = currentState;
}