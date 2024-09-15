#include "ImSender.h"
#include <SoftwareSerial.h>

ImSender::ImSender(HardwareSerial &serial, unsigned long baudrate)
    : serial(serial) {
  serial.begin(baudrate);
}

ImSender::ImSender(SoftwareSerial &serial, unsigned long baudrate)
    : serial(serial) {
  serial.begin(baudrate);
}