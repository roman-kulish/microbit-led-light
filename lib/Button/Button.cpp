#include "Button.h"

void Button::onPress(ButtonCallback fn)
{
    callback = fn;
}

void Button::processButton()
{
    if (!callback)
    {
        return; // nothing to call, nothing to handle
    }

    const uint32_t timeNow = millis();
    if (timeNow - lastDebounceTime < debounceDelay)
    {
        return;
    }

    bool currentState = (digitalRead(pin) == LOW);

    if (currentState && !previousButtonState)
    {
        callback();
    }

    lastDebounceTime = timeNow;
    previousButtonState = currentState;
}