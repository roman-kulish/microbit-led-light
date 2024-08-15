#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#undef min
#undef max

#include <functional>

class Button
{
public:
    explicit Button(uint32_t pin, uint32_t debounceDelay = 30) : m_pin(pin), m_debounceDelay(debounceDelay)
    {
        pinMode(pin, INPUT_PULLUP);
    }

    void onPress(std::function<void()> callback);
    void processButton();

private:
    uint32_t m_pin;
    std::function<void()> m_callback;

    uint32_t m_debounceDelay;
    uint32_t m_lastDebounceTime = 0;
    bool m_previousButtonState = false;
};

#endif
