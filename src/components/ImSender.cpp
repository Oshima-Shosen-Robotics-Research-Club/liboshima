#include "ImSender.h"

ImSender::ImSender(uint8_t rxPin, uint8_t txPin, long baudRate)
    : serial(rxPin, txPin) {
  serial.begin(baudRate);
}