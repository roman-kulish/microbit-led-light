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
        uint8_t address;
        float gain;
        uint16_t integrationTime;
        uint8_t protect;
        bool powerSaveEnabled;
        uint16_t powerSaveMode;
        float minLux;
        float maxLux;
        uint8_t minBrightness;
        uint8_t maxBrightness;
        uint8_t nightModeThreshold;
        float filterWeight = 0.1f;

        VEML6030Config(
            uint8_t address = 0x10,          // Default I2C address
            float gain = 1.0f,               // Default gain (1/8)
            uint16_t integrationTime = 100,  // Default integration time (100ms)
            uint8_t protect = 1,             // Default interrupt/alert protection
            bool powerSaveEnabled = true,    // Default power-saving mode on
            uint16_t powerSaveMode = 4,      // Default power-saving mode (mode 4)
            float minLux = 0.0f,             // Default minimum lux level
            float maxLux = 500.0f,           // Default maximum lux level
            uint8_t minBrightness = 5,       // Default minimum LED brightness
            uint8_t maxBrightness = 255,     // Default maximum LED brightness
            uint8_t nightModeThreshold = 10, // Default night mode threshold
            float filterWeight = 0.1f) : address(address),
                                         gain(gain),
                                         integrationTime(integrationTime),
                                         protect(protect),
                                         powerSaveEnabled(powerSaveEnabled),
                                         powerSaveMode(powerSaveMode),
                                         minLux(minLux),
                                         maxLux(maxLux),
                                         minBrightness(minBrightness),
                                         maxBrightness(maxBrightness),
                                         nightModeThreshold(nightModeThreshold),
                                         filterWeight(filterWeight) {};
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
