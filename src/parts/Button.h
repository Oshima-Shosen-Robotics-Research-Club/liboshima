#pragma once

#include <stdint.h>

class Button {
public:
  Button(uint8_t pin);
  bool isPressed();

private:
  uint8_t pin;
};