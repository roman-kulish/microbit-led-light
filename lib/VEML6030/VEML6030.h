#ifndef VEML6030_H
#define VEML6030_H

#include <Arduino.h>

#include <Wire.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"

// https://learn.sparkfun.com/tutorials/qwiic-ambient-light-sensor-veml6030-hookup-guide
// https://github.com/CoreElectronics/CE-PiicoDev-VEML6030-MicroPython-Module

namespace Sensor
{
    class VEML6030
    {
    public:
        explicit VEML6030(uint8_t address = 0x10) : sensor(address) {}

        void setGain(float gain);
        void setIntegrationTime(uint16_t integrationTime);
        void setProtect(uint8_t protect);
        void setPowerSaveEnabled(bool powerSaveEnabled);
        void setPowerSaveMode(uint16_t powerSaveMode);
        void setLuxRange(float minLux, float maxLux);
        void setBrightnessRange(uint8_t minBrightness, uint8_t maxBrightness);
        void setLowPassFilterWeight(float weight);

        bool begin(TwoWire &wire = Wire);
        float readLux();
        uint8_t getBrightness();

    private:
        SparkFun_Ambient_Light sensor;

        float filteredLux = 0.0f;

        float minLux = 0.0f;             // Default minimum lux level
        float maxLux = 500.0f;           // Default maximum lux level

        uint8_t minBrightness = 5;       // Default minimum LED brightness
        uint8_t maxBrightness = 255;     // Default maximum LED brightness

        float filterWeight = 0.1f;       // Default filter weight for low-pass filter
    };
}

#endif
