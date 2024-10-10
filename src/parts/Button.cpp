#include "Button.h"
#include <Arduino.h>
#include <digitalWriteFast.h>

Button::Button(uint8_t pin) : pin(pin) { pinModeFast(pin, INPUT_PULLUP); }

bool Button::isPressed() { return !digitalReadFast(pin); }