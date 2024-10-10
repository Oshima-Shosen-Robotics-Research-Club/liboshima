#pragma once

#include <stdint.h>

class Led {
public:
  Led(uint8_t pin);
  void on();
  void off();
  void toggle();

private:
  uint8_t pin;
};