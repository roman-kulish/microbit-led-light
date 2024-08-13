#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

typedef void (*ButtonCallback)(void);

class Button
{
public:
    explicit Button(uint32_t pin, unsigned long debounceDelay = 30) : pin(pin), debounceDelay(debounceDelay)
    {
        pinMode(pin, INPUT_PULLUP);
    }

    void onPress(ButtonCallback callback);
    void processButton();

private:
    uint32_t pin;

    ButtonCallback callback;

    uint32_t debounceDelay;
    uint32_t lastDebounceTime = 0;
    bool previousButtonState = false;
};

#endif
