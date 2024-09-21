#include "SerialPort.h"

// HardwareSerial用コンストラクタ
SerialPort::SerialPort(HardwareSerial &serial) {
  hwSerial = &serial;
  swSerial = nullptr;
  fwSerial = nullptr;
  serialType = HARDWARE;
}

// SoftwareSerial用コンストラクタ
SerialPort::SerialPort(SoftwareSerial &serial) {
  hwSerial = nullptr;
  swSerial = &serial;
  fwSerial = nullptr;
  serialType = SOFTWARE;
}

// FastSerial用コンストラクタ
SerialPort::SerialPort(FastwareSerial &serial) {
  hwSerial = nullptr;
  swSerial = nullptr;
  fwSerial = &serial;
  serialType = FASTWARE;
}

// 各関数の実装はシリアルタイプに応じてメンバ関数を呼び出す
void SerialPort::begin(unsigned long baudrate) {
  if (serialType == HARDWARE)
    hwSerial->begin(baudrate);
  else if (serialType == SOFTWARE)
    swSerial->begin(baudrate);
  else if (serialType == FASTWARE)
    fwSerial->begin(baudrate);
}

uint8_t SerialPort::available() {
  if (serialType == HARDWARE)
    return hwSerial->available();
  else if (serialType == SOFTWARE)
    return swSerial->available();
  else if (serialType == FASTWARE)
    return fwSerial->available();
  return 0;
}

char SerialPort::read() {
  if (serialType == HARDWARE)
    return hwSerial->read();
  else if (serialType == SOFTWARE)
    return swSerial->read();
  else if (serialType == FASTWARE)
    return fwSerial->read();
  return 0;
}

uint8_t SerialPort::readBytesUntil(char terminator, char *buffer,
                                   uint8_t length) {
  if (serialType == HARDWARE)
    return hwSerial->readBytesUntil(terminator, buffer, length);
  else if (serialType == SOFTWARE)
    return swSerial->readBytesUntil(terminator, buffer, length);
  else if (serialType == FASTWARE)
    return fwSerial->readBytesUntil(terminator, buffer, length);
  return 0;
}

uint8_t SerialPort::print(const char *str) {
  if (serialType == HARDWARE)
    return hwSerial->print(str);
  else if (serialType == SOFTWARE)
    return swSerial->print(str);
  else if (serialType == FASTWARE)
    return fwSerial->print(str);
  return 0;
}

uint8_t SerialPort::print(int value) {
  if (serialType == HARDWARE)
    return hwSerial->print(value);
  else if (serialType == SOFTWARE)
    return swSerial->print(value);
  else if (serialType == FASTWARE)
    return fwSerial->print(value);
  return 0;
}

uint8_t SerialPort::println(const char *str) {
  if (serialType == HARDWARE)
    return hwSerial->println(str);
  else if (serialType == SOFTWARE)
    return swSerial->println(str);
  else if (serialType == FASTWARE)
    return fwSerial->println(str);
  return 0;
}

uint8_t SerialPort::println() {
  if (serialType == HARDWARE)
    return hwSerial->println();
  else if (serialType == SOFTWARE)
    return swSerial->println();
  else if (serialType == FASTWARE)
    return fwSerial->println();
  return 0;
}