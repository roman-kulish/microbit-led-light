#include <Arduino.h>
#include <Adafruit_Microbit.h>
#include <Wire.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"
#include "VEML6030.h"
#include "Button.h"
#include "State.h"
#include "matrix.h"
#include <WS2812FX.h>

Adafruit_Microbit uBit{};

SparkFun_Ambient_Light lightSensor{0x10};
Sensor::VEML6030 light{&lightSensor};

WS2812FX ws2812fx{120, PIN_A0, NEO_GRB};

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

  if (!lightSensor.begin())
  {
    Serial.println("Ambient light sensor not found. Halting ...");

    while (true)
      ; // Hang here
  }

  lightSensor.setGain(2);
  lightSensor.setIntegTime(400);
  lightSensor.disablePowSave();

  uBit.begin();

  ws2812fx.init();
  ws2812fx.setMode(state.getPattern());

  uint32_t colors[] = {BLUE, YELLOW, GREEN};
  ws2812fx.setColors(0, colors);

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
