#pragma once

#include <stddef.h>

// 実装を強制するためだけに作られた純粋仮想関数を持つ抽象クラス
class _FastSerialBase {
public:
  virtual void begin(unsigned long baudrate) = 0;
  virtual size_t available() = 0;
  virtual char read() = 0;
  virtual size_t readBytesUntil(char terminator, char *buffer,
                                size_t length) = 0;
  virtual size_t print(const char *str) = 0;
  virtual size_t println(const char *str) = 0;
  virtual void onReceive(void (*function)(void)) = 0;
  static void (*user_onReceive)(void); // 静的メンバ変数として宣言
};