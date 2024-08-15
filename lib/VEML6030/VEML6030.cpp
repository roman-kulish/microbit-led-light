#include "VEML6030.h"

#undef min
#undef max

#include <algorithm>

namespace Sensor
{
    bool VEML6030::begin(SparkFun_Ambient_Light *sensor)
    {
        if (sensor == nullptr)
        {
            return false;
        }

        m_sensor = sensor;
        m_sensor->begin();

        return true;
    }

    void VEML6030::setLuxRange(float minLux, float maxLux)
    {
        if (minLux < 0 || maxLux < 0 || minLux >= maxLux)
        {
            return; // invalid range
        }

        m_minLux = minLux;
        m_maxLux = maxLux;
    }

    void VEML6030::setBrightnessRange(uint8_t minBrightness, uint8_t maxBrightness)
    {
        if (minBrightness < 0 || maxBrightness < 0 || minBrightness >= maxBrightness)
        {
            return; // invalid range
        }

        m_minBrightness = minBrightness;
        m_maxBrightness = maxBrightness;
    }

    void VEML6030::setLowPassFilterWeight(float weight)
    {
        if (weight < 0 || weight > 1)
        {
            return; // invalid weight
        }

        m_filterWeight = weight;
    }

    float VEML6030::readLux()
    {
        if (m_sensor == nullptr)
        {
            return 0.0f; // sensor not initialized
        }

        const float lux = m_sensor->readLight();

        m_filteredLux = m_filterWeight * lux + (1 - m_filterWeight) * m_filteredLux; // apply low-pass filter
        return m_filteredLux;
    }

    uint8_t VEML6030::getBrightness()
    {
        float lux = std::max(m_minLux, std::min(readLux(), m_maxLux));
        float ratio = (lux - m_minLux) / (m_maxLux - m_minLux);

        uint8_t brightness = static_cast<uint8_t>(ratio * (m_maxBrightness - m_minBrightness) + m_minBrightness);

        return std::max(m_minBrightness, std::min(brightness, m_maxBrightness));
    }
}
