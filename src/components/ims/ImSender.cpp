#include "ImSender.h"
#include <SoftwareSerial.h>

ImSender::ImSender(HardwareSerial &serial, long baudRate) : serial(serial) {
  // シリアル通信を指定されたボーレートで開始
  serial.begin(baudRate);
}

ImSender::ImSender(SoftwareSerial &serial, long baudRate) : serial(serial) {
  // シリアル通信を指定されたボーレートで開始
  serial.begin(baudRate);
}