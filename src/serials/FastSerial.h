#pragma once

#include "_FastSerialBase.h"
#include <avr/interrupt.h>

// ATmega328Pの場合
#if defined(__AVR_ATmega328P__)
class FastSerial : public _FastSerialBase {
public:
  // シリアル通信の初期化
  void begin(unsigned long baudrate) override;

  // 受信バッファにデータがあるかどうかをチェック
  size_t available() override;

  // 1バイトのデータを受信
  char read() override;

  // 指定した文字が受信されるまでデータを読み込む
  size_t readBytesUntil(char terminator, char *buffer, size_t length) override;

  // 文字列を送信
  size_t print(const char *str) override;

  // 文字列を送信して改行
  size_t println(const char *str) override;

  // ユーザー定義のコールバック関数を登録
  void onReceive(void (*function)(void)) override;
};

extern FastSerial FSerial;
#endif