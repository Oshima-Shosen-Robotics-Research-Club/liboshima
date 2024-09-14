#include "ImSender.h"
#include <SoftwareSerial.h>

ImSender::ImSender(int rxPin, int txPin, bool isSoftwareSerial,
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
