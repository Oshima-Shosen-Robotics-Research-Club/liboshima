#pragma once

#include <Arduino.h>

/**
 * @class NonSpeedAdjustable
 * @brief A class to control a motor without speed adjustment capabilities.
 * 
 * This class provides basic functionalities to control a motor's direction
 * (forward and reverse) and to stop the motor. It does not support speed
 * adjustment.
 */
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
