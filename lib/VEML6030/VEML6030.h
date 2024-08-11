#ifndef VEML6030_H
#define VEML6030_H

#include <Arduino.h>

#include <Wire.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"

// https://learn.sparkfun.com/tutorials/qwiic-ambient-light-sensor-veml6030-hookup-guide
// https://github.com/CoreElectronics/CE-PiicoDev-VEML6030-MicroPython-Module

namespace Sensor
{
    // Configuration struct for VEML6030
    struct VEML6030Config
    {
        uint8_t address = 0x10;          // Default I2C address
        float gain = 1.0f;               // Default gain (1/8)
        uint16_t integrationTime = 100;  // Default integration time (100ms)
        uint8_t protect = 1;             // Default interrupt/alert protection
        bool powerSaveEnabled = true;    // Default power-saving mode on
        uint16_t powerSaveMode = 4;      // Default power-saving mode (mode 4)
        float minLux = 0.0f;             // Default minimum lux level
        float maxLux = 500.0f;           // Default maximum lux level
        uint8_t minBrightness = 5;       // Default minimum LED brightness
        uint8_t maxBrightness = 255;     // Default maximum LED brightness
        uint8_t nightModeThreshold = 10; // Default night mode threshold
        float filterWeight = 0.1f;       // Default filter weight for low-pass filter
    };

    class VEML6030ConfigBuilder
    {
    public:
        VEML6030ConfigBuilder &setAddress(uint8_t address)
        {
            config.address = address;
            return *this;
        }

        VEML6030ConfigBuilder &setGain(float gain)
        {
            config.gain = gain;
            return *this;
        }

        VEML6030ConfigBuilder &setIntegrationTime(uint16_t integrationTime)
        {
            config.integrationTime = integrationTime;
            return *this;
        }

        VEML6030ConfigBuilder &setProtect(uint8_t protect)
        {
            config.protect = protect;
            return *this;
        }

        VEML6030ConfigBuilder &setPowerSaveEnabled(bool powerSaveEnabled)
        {
            config.powerSaveEnabled = powerSaveEnabled;
            return *this;
        }

        VEML6030ConfigBuilder &setPowerSaveMode(uint16_t powerSaveMode)
        {
            config.powerSaveMode = powerSaveMode;
            return *this;
        }

        VEML6030ConfigBuilder &setMinLux(float minLux)
        {
            config.minLux = minLux;
            return *this;
        }

        VEML6030ConfigBuilder &setMaxLux(float maxLux)
        {
            config.maxLux = maxLux;
            return *this;
        }

        VEML6030ConfigBuilder &setMinBrightness(uint8_t minBrightness)
        {
            config.minBrightness = minBrightness;
            return *this;
        }

        VEML6030ConfigBuilder &setMaxBrightness(uint8_t maxBrightness)
        {
            config.maxBrightness = maxBrightness;
            return *this;
        }

        VEML6030ConfigBuilder &setNightModeThreshold(uint8_t nightModeThreshold)
        {
            config.nightModeThreshold = nightModeThreshold;
            return *this;
        }

        VEML6030ConfigBuilder &setFilterWeight(float filterWeight)
        {
            config.filterWeight = filterWeight;
            return *this;
        }

        VEML6030Config build()
        {
            return config;
        }

    private:
        VEML6030Config config;
    };

    class VEML6030
    {
    public:
        explicit VEML6030(const VEML6030Config &config) : config(config), sensor(config.address) {}

        bool begin(TwoWire &wire = Wire);
        float readLux();
        uint8_t getBrightness();
        bool isNightMode();

    private:
        const VEML6030Config config;
        SparkFun_Ambient_Light sensor;

        float filteredLux = 0.0f;
    };
}

#endif
