#include "State.h"

const std::vector<uint8_t> State::m_patternSequence = {
    // FX_MODE_BLINK,
    // FX_MODE_BREATH,
    // FX_MODE_COLOR_WIPE,
    // FX_MODE_COLOR_WIPE_INV,
    // FX_MODE_COLOR_WIPE_REV,
    // FX_MODE_COLOR_WIPE_REV_INV,
    FX_MODE_COLOR_WIPE_RANDOM,
    // FX_MODE_RANDOM_COLOR,
    FX_MODE_SINGLE_DYNAMIC,
    FX_MODE_MULTI_DYNAMIC,
    FX_MODE_RAINBOW,
    FX_MODE_RAINBOW_CYCLE,
    // FX_MODE_SCAN,
    // FX_MODE_DUAL_SCAN,
    // FX_MODE_FADE,
    // FX_MODE_THEATER_CHASE,
    // FX_MODE_THEATER_CHASE_RAINBOW,
    FX_MODE_RUNNING_LIGHTS,
    // FX_MODE_TWINKLE,
    FX_MODE_TWINKLE_RANDOM,
    // FX_MODE_TWINKLE_FADE,
    // FX_MODE_TWINKLE_FADE_RANDOM,
    // FX_MODE_SPARKLE,
    FX_MODE_FLASH_SPARKLE,
    // FX_MODE_HYPER_SPARKLE,
    // FX_MODE_STROBE,
    // FX_MODE_STROBE_RAINBOW,
    // FX_MODE_MULTI_STROBE,
    // FX_MODE_BLINK_RAINBOW,
    // FX_MODE_CHASE_WHITE,
    // FX_MODE_CHASE_COLOR,
    // FX_MODE_CHASE_RANDOM,
    FX_MODE_CHASE_RAINBOW,
    // FX_MODE_CHASE_FLASH,
    // FX_MODE_CHASE_FLASH_RANDOM,
    // FX_MODE_CHASE_RAINBOW_WHITE,
    // FX_MODE_CHASE_BLACKOUT,
    // FX_MODE_CHASE_BLACKOUT_RAINBOW,
    FX_MODE_COLOR_SWEEP_RANDOM,
    // FX_MODE_RUNNING_COLOR,
    // FX_MODE_RUNNING_RED_BLUE,
    FX_MODE_RUNNING_RANDOM,
    FX_MODE_LARSON_SCANNER,
    // FX_MODE_COMET,
    // FX_MODE_FIREWORKS,
    FX_MODE_FIREWORKS_RANDOM,
    FX_MODE_MERRY_CHRISTMAS,
    // FX_MODE_FIRE_FLICKER,
    // FX_MODE_FIRE_FLICKER_SOFT,
    // FX_MODE_FIRE_FLICKER_INTENSE,
    // FX_MODE_CIRCUS_COMBUSTUS,
    FX_MODE_HALLOWEEN,
    // FX_MODE_BICOLOR_CHASE,
    // FX_MODE_TRICOLOR_CHASE,
    FX_MODE_TWINKLEFOX,
    // FX_MODE_RAIN,
};

void State::OnStateChange(std::function<void(bool)> callback)
{
    m_stateChangeCallback = callback;
}

void State::OnPatternChange(std::function<void(uint8_t pattern)> callback)
{
    m_patternChangeCallback = callback;
}

void State::setState(bool on)
{
    m_isOn = on;

    if (m_stateChangeCallback)
    {
        m_stateChangeCallback(isOn());
    }
}

void State::toggle()
{
    m_isOn = !m_isOn;

    if (m_stateChangeCallback)
    {
        m_stateChangeCallback(isOn());
    }
}

bool State::isOn() const
{
    return m_isOn;
}

void State::nextPattern()
{
    m_pattern = (m_pattern + 1) % m_patternSequence.size();

    if (m_patternChangeCallback)
    {
        m_patternChangeCallback(getPattern());
    }

    if (!isOn())
    {
        setState(true); // act as an on-switch

        if (m_stateChangeCallback)
        {
            m_stateChangeCallback(isOn());
        }
    }
}

uint8_t State::getPattern() const
{
    return m_patternSequence[m_pattern];
}
