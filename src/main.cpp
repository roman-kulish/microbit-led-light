#include <Arduino.h>
#include <Adafruit_Microbit.h>
#include <Wire.h>
#include "VEML6030.h"
#include "Button.h"
#include "State.h"
#include "matrix.h"

Adafruit_Microbit uBit{};
State state{};

Sensor::VEML6030 light{Sensor::VEML6030ConfigBuilder{}
                           .setGain(2)
                           .setIntegrationTime(800)
                           .setPowerSaveEnabled(false)
                           .build()};

Button buttonA{PIN_BUTTON_A, []()
               { state.nextMode(); }};
Button buttonB{PIN_BUTTON_B, []()
               { state.nextPattern(); }};

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  Wire.begin();

  uBit.begin();

  if (!light.begin(Wire))
  {
    Serial.println("Ambient light sensor not found. Halting ...");

    while (true)
      ; // Hang here
  }
}

void loop()
{
  buttonA.processButton();
  buttonB.processButton();

  static Mode previousMode;
  Mode currentMode = state.getMode();

  if (currentMode != previousMode)
  {
    switch (currentMode)
    {
    case Mode::ON:
      uBit.matrix.show(IMAGE_MODE_ON);
      break;

    case Mode::MOTION_DETECTED:
      uBit.matrix.show(IMAGE_MODE_MOTION_DETECTED);
      break;

    case Mode::OFF:
      uBit.matrix.show(IMAGE_MODE_OFF);
      break;
    }

    previousMode = currentMode;
  }

  // const uint8_t brightness = light.getBrightness();
}
