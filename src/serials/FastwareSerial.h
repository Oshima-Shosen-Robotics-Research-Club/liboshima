#pragma once

#include <stddef.h>
#include <stdint.h>

class FastwareSerial {
public:
  void begin(unsigned long baudrate);
  uint8_t available();
  char read();
  uint8_t readBytesUntil(char terminator, char *buffer, uint8_t length);
  uint8_t write(uint8_t data);
  uint8_t print(const char *str);
  uint8_t print(uint8_t value);
  uint8_t println(const char *str);
  uint8_t println();
  void onReceive(void (*function)(void));
  void (*user_onReceive)(void);
};

extern FastwareSerial FastSerial;
