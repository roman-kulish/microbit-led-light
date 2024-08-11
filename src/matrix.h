#include <Arduino.h>

static constexpr uint8_t IMAGE_MODE_ON[5] = {
    B00000,
    B01010,
    B00000,
    B10001,
    B01110};

static constexpr uint8_t IMAGE_MODE_MOTION_DETECTED[5] = {
    B01111,
    B11010,
    B11100,
    B11110,
    B01111};

static constexpr uint8_t IMAGE_MODE_OFF[5] = {
    B00000,
    B01010,
    B00000,
    B01110,
    B10001};