#include "SerialPort.h"

SerialPort::SerialPort(HardwareSerial &serial, unsigned long baudrate) {
  begin = [&serial](unsigned long baudrate) { serial.begin(baudrate); };
  available = [&serial]() { return serial.available(); };
  read = [&serial]() { return serial.read(); };
  readBytesUntil = [&serial](char terminator, char *buffer, size_t length) {
    return serial.readBytesUntil(terminator, buffer, length);
  };
  print = [&serial](const char *str) { return serial.print(str); };
  println = [&serial](const char *str) { return serial.println(str); };

  begin(baudrate);
}