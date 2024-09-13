#include "ImReceiver.h"
#include <SoftwareSerial.h>

ImReceiver::ImReceiver(HardwareSerial &serial, long baudRate)
    : serial(serial) {
  // シリアル通信を指定されたボーレートで開始
  serial.begin(baudRate);
}

ImReceiver::ImReceiver(SoftwareSerial &serial, long baudRate)
    : serial(serial) {
  // シリアル通信を指定されたボーレートで開始
  serial.begin(baudRate);
}

// データが利用可能かどうかをチェックするメソッド
bool ImReceiver::available() { return serial.available(); }