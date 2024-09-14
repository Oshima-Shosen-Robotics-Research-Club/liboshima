#include "ImReceiver.h"
#include <SoftwareSerial.h>

ImReceiver::ImReceiver(int rxPin, int txPin, bool isSoftwareSerial,
                       unsigned long baudrate)
    : serial(isSoftwareSerial ? (Stream *)new SoftwareSerial(rxPin, txPin)
                              : (Stream *)&Serial) {
  // シリアル通信を指定されたボーレートで開始
  if (isSoftwareSerial) {
    ((SoftwareSerial *)serial)->begin(baudrate);
  } else {
    ((HardwareSerial *)serial)->begin(baudrate);
  }
}

// データが利用可能かどうかをチェックするメソッド
bool ImReceiver::available() { return serial->available(); }