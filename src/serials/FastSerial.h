#pragma once

#include <Arduino.h>
#include <avr/interrupt.h>

// レジスタ操作で作られた高速シリアル通信のクラス

// ATmega328Pの場合
#if defined(__AVR_ATmega328P__)
class FastSerial {
public:
  void begin(unsigned long baudrate);
  size_t available();
  char read();
  size_t readBytesUntil(char terminator, char *buffer, size_t length);
  size_t print(const char *str);
  size_t println(const char *str);
  void onReceive(void (*function)(void));
};
#endif