#include "ImReceiver.h"

ImReceiver::ImReceiver(uint8_t rxPin, uint8_t txPin, long baudRate)
    : serial(rxPin, txPin) {
  serial.begin(baudRate);
}

bool ImReceiver::available() { return serial.available(); }