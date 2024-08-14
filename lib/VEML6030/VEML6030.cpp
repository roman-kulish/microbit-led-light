#include "VEML6030.h"

#undef min
#undef max

#include <algorithm>

namespace Sensor
{
    void VEML6030::setLuxRange(float minLux, float maxLux)
    {
        this->minLux = minLux;
        this->maxLux = maxLux;
    }

    void VEML6030::setBrightnessRange(uint8_t minBrightness, uint8_t maxBrightness)
    {
        this->minBrightness = minBrightness;
        this->maxBrightness = maxBrightness;
    }

    void VEML6030::setLowPassFilterWeight(float weight)
    {
        filterWeight = weight;
    }

    float VEML6030::readLux()
    {
        const float lux = sensor->readLight();

        filteredLux = filterWeight * lux + (1 - filterWeight) * filteredLux; // apply low-pass filter
        return filteredLux;
    }

    uint8_t VEML6030::getBrightness()
    {
        float lux = std::max(minLux, std::min(readLux(), maxLux));
        float ratio = (lux - minLux) / (maxLux - minLux);

        uint8_t brightness = ratio * (maxBrightness - minBrightness) + minBrightness;

        return std::max(minBrightness, std::min(brightness, maxBrightness));
    }
}
