#pragma once

#include <Arduino.h>

class NonSpeedAdjustable {
public:
  NonSpeedAdjustable(uint8_t pin1, uint8_t pin2);
  void forward();
  void reverse();
  void stop();

private:
  uint8_t pin1;
  uint8_t pin2;
};
