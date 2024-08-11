#include "VEML6030.h"

namespace Sensor
{
    bool VEML6030::begin(TwoWire &wire)
    {
        if (!sensor.begin(wire))
        {
            return false; // Sensor not found
        }

        sensor.setGain(config.gain);
        sensor.setIntegTime(config.integrationTime);
        sensor.setProtect(config.protect);

        if (config.powerSaveEnabled)
        {
            sensor.enablePowSave();
            sensor.setPowSavMode(config.powerSaveMode);
        }

        return true;
    }

    float VEML6030::readLux()
    {
        float newLux = sensor.readLight();
        filteredLux = config.filterWeight * newLux + (1 - config.filterWeight) * filteredLux; // apply low-pass filter

        return filteredLux;
    }

    uint8_t VEML6030::getBrightness()
    {
        float lux = readLux();
        lux = max(config.minLux, min(lux, config.maxLux));

        float ratio = (lux - config.minLux) / (config.maxLux - config.minLux);
        uint8_t led_brightness = static_cast<uint8_t>(ratio * (config.maxBrightness - config.minBrightness)) + config.minBrightness;

        return max(config.minBrightness, min(led_brightness, config.maxBrightness));
    }

    bool VEML6030::isNightMode()
    {
        return getBrightness() < config.nightModeThreshold;
    }
}
