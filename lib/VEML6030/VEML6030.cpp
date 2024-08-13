#include "VEML6030.h"

#undef min
#undef max

#include <algorithm>

namespace Sensor
{
    void VEML6030::setGain(float gain)
    {
        sensor.setGain(gain);
    }

    void VEML6030::setIntegrationTime(uint16_t integrationTime)
    {
        sensor.setIntegTime(integrationTime);
    }

    void VEML6030::setProtect(uint8_t protect)
    {
        sensor.setProtect(protect);
    }

    void VEML6030::setPowerSaveEnabled(bool powerSaveEnabled)
    {
        if (powerSaveEnabled)
        {
            sensor.enablePowSave();
        }
        else
        {
            sensor.disablePowSave();
        }
    }

    void VEML6030::setPowerSaveMode(uint16_t powerSaveMode)
    {
        sensor.setPowSavMode(powerSaveMode);
    }

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

    bool VEML6030::begin(TwoWire &wire)
    {
        if (!sensor.begin(wire))
        {
            return false; // Sensor not found
        }

        return true;
    }

    float VEML6030::readLux()
    {
        return sensor.readLight();
    }

    uint8_t VEML6030::getBrightness()
    {
        filteredLux = filterWeight * readLux() + (1 - filterWeight) * filteredLux; // apply low-pass filter

        float lux = std::max(minLux, std::min(filteredLux, maxLux));
        float ratio = (lux - minLux) / (maxLux - minLux);

        uint8_t brightness = static_cast<uint8_t>(ratio * (maxBrightness - minBrightness)) + minBrightness;

        return std::max(minBrightness, std::min(brightness, maxBrightness));
    }
}
