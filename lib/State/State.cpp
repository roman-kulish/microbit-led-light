#include "State.h"

static std::unordered_map<uint8_t, Mode> modeSequence = {
    {0, Mode::OFF},
    {1, Mode::ON},
    {2, Mode::MOTION_DETECTED}};

void State::nextMode()
{
    mode = (mode + 1) % modeSequence.size();
}

Mode State::getMode() const
{
    return modeSequence.at(mode);
}

void State::nextPattern()
{
    pattern = (pattern + 1) % patternSequence.size();
    mode = getMode() == Mode::OFF ? 1 : mode; // act as an on-switch
}

uint8_t State::getPattern() const
{
    return patternSequence[pattern];
}