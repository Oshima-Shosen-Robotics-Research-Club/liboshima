#include "NonAdjustable.h"
#include <digitalWriteFast.h>

NonAdjustable::NonAdjustable(uint8_t pin1, uint8_t pin2)
    : pin1(pin1), pin2(pin2) {
  pinModeFast(pin1, OUTPUT);
  pinModeFast(pin2, OUTPUT);
}

void NonAdjustable::forward() {
  digitalWriteFast(pin1, HIGH);
  digitalWriteFast(pin2, LOW);
}

void NonAdjustable::reverse() {
  digitalWriteFast(pin1, LOW);
  digitalWriteFast(pin2, HIGH);
}

void NonAdjustable::stop() {
  digitalWriteFast(pin1, HIGH);
  digitalWriteFast(pin2, HIGH);
}