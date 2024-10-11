#pragma once

#include <Arduino.h>
#include <digitalWriteFast.h>
#include <stdint.h>

class Led {
public:
  Led(uint8_t pin) : pin(pin) { pinModeFast(pin, OUTPUT); }
  void on() { digitalWriteFast(pin, HIGH); }
  void off() { digitalWriteFast(pin, LOW); }
  void toggle() { digitalWriteFast(pin, !digitalReadFast(pin)); }

private:
  uint8_t pin;
};