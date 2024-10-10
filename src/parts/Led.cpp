#include "Led.h"
#include <Arduino.h>
#include <digitalWriteFast.h>

Led::Led(uint8_t pin) : pin(pin) { pinModeFast(pin, OUTPUT); }

void Led::on() { digitalWriteFast(pin, HIGH); }

void Led::off() { digitalWriteFast(pin, LOW); }

void Led::toggle() { digitalWriteFast(pin, !digitalReadFast(pin)); }