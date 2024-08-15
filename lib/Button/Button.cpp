#include "Button.h"

void Button::onPress(std::function<void()> callback)
{
    m_callback = callback;
}

void Button::processButton()
{
    if (!m_callback)
    {
        return; // nothing to call, nothing to handle
    }

    const uint32_t timeNow = millis();
    if (timeNow - m_lastDebounceTime < m_debounceDelay)
    {
        return;
    }

    bool currentState = (digitalRead(m_pin) == LOW);

    if (currentState && !m_previousButtonState)
    {
        m_callback();
    }

    m_lastDebounceTime = timeNow;
    m_previousButtonState = currentState;
}