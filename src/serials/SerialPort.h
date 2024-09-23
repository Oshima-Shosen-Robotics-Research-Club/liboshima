#pragma once

#if defined(USE_FASTWARE_SERIAL)
#include "FastwareSerial.h"
#else
#include <HardwareSerial.h>
#endif
#include <SoftwareSerial.h>

#include <stddef.h>
#include <stdint.h>

/**
 * シリアル通信を抽象化するクラス
 */
class SerialPort {
public:
// コンストラクタは異なるシリアルオブジェクトを受け取る
#if defined(USE_FASTWARE_SERIAL)
  SerialPort(FastwareSerial &serial);
#else
  SerialPort(HardwareSerial &serial);
#endif
  SerialPort(SoftwareSerial &serial);

  // 関数ポインタが使えないため
  void begin(unsigned long baudrate);
  uint8_t available();
  char read();
  uint8_t readBytesUntil(char terminator, char *buffer, uint8_t length);
  uint8_t print(const char *str);
  uint8_t print(int value);
  uint8_t println(const char *str);
  uint8_t println();

private:
// 基本シリアルオブジェクトへのポインタ
#if defined(USE_FASTWARE_SERIAL)
  FastwareSerial *hwSerial; // dummy
  SoftwareSerial *swSerial;
  FastwareSerial *fwSerial;
#else
  HardwareSerial *hwSerial;
  SoftwareSerial *swSerial;
  HardwareSerial *fwSerial; // dummy
#endif

  // どのシリアルが有効かを示すフラグ
  enum SerialType { NONE, HARDWARE, SOFTWARE, FASTWARE } serialType;
};
