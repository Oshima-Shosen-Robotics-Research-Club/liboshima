#pragma once

#include <Arduino.h>
#include <digitalWriteFast.h>
#include <stdint.h>

class Button {
public:
  Button(uint8_t pin) : pin(pin) { pinModeFast(pin, INPUT_PULLUP); }
  bool isPressed() { return digitalReadFast(pin) == LOW; }

private:
  uint8_t pin;
};