#pragma once

#include "FastSerial.h"
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include <stddef.h>
#include <stdint.h>

/** 
 * シリアル通信を抽象化するクラス
*/
class SerialPort {
public:
  // コンストラクタは異なるシリアルオブジェクトを受け取る
  SerialPort(HardwareSerial &serial);
  SerialPort(SoftwareSerial &serial);
  SerialPort(FastSerial &serial);

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
  HardwareSerial *hwSerial;
  SoftwareSerial *swSerial;
  FastSerial *fSerial;

  // どのシリアルが有効かを示すフラグ
  enum SerialType { NONE, HARDWARE, SOFTWARE, FAST } serialType;
};
