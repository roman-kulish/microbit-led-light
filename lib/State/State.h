#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

#undef min
#undef max

#include <array>
#include <unordered_map>

enum class Mode
{
    ON,
    MOTION_DETECTED,
    OFF
};

class State
{
public:
    State() = default;

    void nextMode();
    Mode getMode() const;

    void nextPattern();
    uint8_t getPattern() const;

private:
    // static constexpr std::array<Mode, 3> modeSequence = {Mode::ON, Mode::MOTION_DETECTED, Mode::OFF};
    static constexpr std::array<uint8_t, 9> patternSequence = {};

    uint8_t mode = 0;
    uint8_t pattern = 0;
};

#endif