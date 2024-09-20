#pragma once

#include <avr/interrupt.h>
#include <stddef.h>
#include <stdint.h>

// ATmega328Pの場合
#if defined(__AVR_ATmega328P__)
class FastSerial {
public:
  // シリアル通信の初期化
  void begin(unsigned long baudrate);

  // 受信バッファにデータがあるかどうかをチェック
  size_t available();

  // 1バイトのデータを受信
  char read();

  // 指定した文字が受信されるまでデータを読み込む
  size_t readBytesUntil(char terminator, char *buffer, size_t length);

  // 文字列を送信
  size_t print(const char *str);

  // 文字列を送信して改行
  size_t println(const char *str);

  // ユーザー定義のコールバック関数を登録
  void onReceive(void (*function)(void));

  static void (*user_onReceive)(void);
};

extern FastSerial FSerial;
#endif