#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include <vector>
#include <functional>
#include "WS2812FX.h"

class State
{
public:
    State() = default;

    void OnStateChange(std::function<void(bool isOn)> callback);
    void OnPatternChange(std::function<void(uint8_t pattern)> callback);

    void setState(bool on);
    void toggle();
    bool isOn() const;

    void nextPattern();
    uint8_t getPattern() const;

private:
    bool m_isOn = false;
    uint8_t m_pattern = 0;

    std::function<void(bool isOn)> m_stateChangeCallback;
    std::function<void(uint8_t pattern)> m_patternChangeCallback;

    static const std::vector<uint8_t> m_patternSequence;
};

#endif