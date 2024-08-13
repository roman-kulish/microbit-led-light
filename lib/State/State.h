#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

#undef min
#undef max

#include <vector>
#include "WS2812FX.h"

enum class Mode
{
    ON,
    MOTION_DETECTED,
    OFF
};

typedef void (*ModeChangeCallback)(Mode);
typedef void (*PatternChangeCallback)(uint8_t);

class State
{
public:
    State() = default;

    void OnModeChange(ModeChangeCallback callback);
    void OnPatternChange(PatternChangeCallback callback);

    void nextMode();
    void setMode(Mode mode);
    Mode getMode() const;

    void nextPattern();
    uint8_t getPattern() const;

private:
    uint8_t mode = 0;
    uint8_t pattern = 0;

    ModeChangeCallback modeChangeCallback;
    PatternChangeCallback patternChangeCallback;

    static const std::vector<Mode> modeSequence;
    static const std::vector<uint8_t> patternSequence;
};

#endif