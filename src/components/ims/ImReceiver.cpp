#include "ImReceiver.h"
#include <SoftwareSerial.h>

// HardwareSerial の場合
ImReceiver::ImReceiver(HardwareSerial &serial, unsigned long baudrate)
    : serial(serial) {
  serial.begin(baudrate);
}

// SoftwareSerial の場合
ImReceiver::ImReceiver(SoftwareSerial &serial, unsigned long baudrate)
    : serial(serial) {
  serial.begin(baudrate);
}

// データが利用可能かどうかをチェックするメソッド
bool ImReceiver::available() { return serial.available(); }
