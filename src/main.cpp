#include <Arduino.h>
#include <Adafruit_Microbit.h>
#include <Wire.h>
#include "VEML6030.h"

Adafruit_Microbit_Matrix microbit{};

Sensor::VEML6030 light(Sensor::VEML6030Config{
    .gain = 2,
    .integrationTime = 800,
    .powerSaveEnabled = false,
});

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  if (!light.begin(Wire))
  {
    Serial.println("Ambient light sensor not found");

    while (true)
      ; // Stop here
  }
}

void loop()
{
}
