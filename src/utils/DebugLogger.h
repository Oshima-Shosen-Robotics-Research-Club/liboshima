#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @class DebugLogger
 * @brief デバッグメッセージをシリアルポートに出力するテンプレートクラス
 */
template <typename SerialType> class DebugLogger {
public:
  DebugLogger(SerialType &serialPort) : serialPort(serialPort) {}

  void begin(unsigned long baudrate = 19200) { serialPort.begin(baudrate); }

  void println(const char *className, const char *methodName,
               const char *message) {
    serialPort.print("<");
    serialPort.print(className);
    serialPort.print("::");
    serialPort.print(methodName);
    serialPort.print("> ");
    serialPort.println(message); // メッセージを出力
  }

  void printlnf(const char *className, const char *methodName,
                const char *format, ...) {
    char buffer[100]; // バッファサイズを設定
    va_list args;
    va_start(args, format); // 可変引数の初期化
    vsnprintf(buffer, sizeof(buffer), format,
              args); // フォーマットされた文字列を作成
    va_end(args);    // 可変引数の解放
    println(className, methodName, buffer); // printlnメソッドを呼び出す
  }

private:
  SerialType &serialPort;
};
