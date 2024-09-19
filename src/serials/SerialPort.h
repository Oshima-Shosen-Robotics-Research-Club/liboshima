#pragma once

#include "FastSerial.h"
#include <HardwareSerial.h>
#include <SoftwareSerial.h>

class SerialPort {
public:
  SerialPort(HardwareSerial &serial, unsigned long baudrate = 19200);
  SerialPort(SoftwareSerial &serial, unsigned long baudrate = 19200);
  SerialPort(FastSerial &serial, unsigned long baudrate = 19200);

  // 関数ポインタ
  void (*begin)(unsigned long baudrate);
  size_t (*available)();
  int (*read)();
  size_t (*readBytesUntil)(char terminator, char *buffer, size_t length);
  size_t (*print)(const char *str);
  size_t (*println)(const char *str);
};