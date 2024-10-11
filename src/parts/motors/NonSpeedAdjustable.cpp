#include "NonSpeedAdjustable.h"
#include <digitalWriteFast.h>

NonSpeedAdjustable::NonSpeedAdjustable(uint8_t pin1, uint8_t pin2)
    : pin1(pin1), pin2(pin2) {
  pinModeFast(pin1, OUTPUT);
  pinModeFast(pin2, OUTPUT);
}

void NonSpeedAdjustable::forward() {
  digitalWriteFast(pin1, HIGH);
  digitalWriteFast(pin2, LOW);
}

void NonSpeedAdjustable::reverse() {
  digitalWriteFast(pin1, LOW);
  digitalWriteFast(pin2, HIGH);
}

void NonSpeedAdjustable::stop() {
  digitalWriteFast(pin1, HIGH);
  digitalWriteFast(pin2, HIGH);
}