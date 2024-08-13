#include <Arduino.h>
#include <Adafruit_Microbit.h>
#include <Wire.h>
#include "VEML6030.h"
#include "Button.h"
#include "State.h"
#include "matrix.h"
#include <WS2812FX.h>

Adafruit_Microbit uBit{};

Sensor::VEML6030 light{};

WS2812FX ws2812fx{30, PIN_A0, NEO_GRB};

Button buttonA{PIN_BUTTON_A};
Button buttonB{PIN_BUTTON_B};

State state{};

void onModeChange(Mode mode)
{
  switch (mode)
  {
  case Mode::ON:
    uBit.matrix.show(IMAGE_MODE_ON);
    ws2812fx.start();
    break;

  case Mode::MOTION_DETECTED:
    uBit.matrix.show(IMAGE_MODE_MOTION_DETECTED);
    break;

  case Mode::OFF:
    uBit.matrix.show(IMAGE_MODE_OFF);
    ws2812fx.stop();
    break;
  }
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  Wire.begin();

  uBit.begin();

  light.setGain(2);
  light.setIntegrationTime(400);
  light.setPowerSaveEnabled(false);

  if (!light.begin(Wire))
  {
    Serial.println("Ambient light sensor not found. Halting ...");

    while (true)
      ; // Hang here
  }

  ws2812fx.init();
  ws2812fx.setMode(state.getPattern());

  buttonA.onPress([]()
                  { state.nextMode(); });

  buttonB.onPress([]()
                  { state.nextPattern(); });

  state.OnModeChange(onModeChange);

  state.OnPatternChange([](uint8_t pattern)
                        {
                           ws2812fx.setMode(pattern); 

                            Serial.print("Pattern changed to: ");
                            Serial.println(ws2812fx.getModeName(pattern)); });

  state.setMode(Mode::OFF);
}

void loop()
{
  buttonA.processButton();
  buttonB.processButton();

  ws2812fx.setBrightness(light.getBrightness());
  ws2812fx.service();
}
