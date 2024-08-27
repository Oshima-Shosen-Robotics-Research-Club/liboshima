#include "DebugLogger.h"
#include <stdarg.h>
#include <stdio.h>

HardwareSerial *DebugLogger::serialPort = nullptr; // 静的メンバーの初期化

void DebugLogger::init(HardwareSerial &port, long baudRate) {
  serialPort = &port;
  serialPort->begin(baudRate);
}

void DebugLogger::print(const char *className, const char *methodName,
                        const char *message) {

  if (serialPort) {
    serialPort->print("<");
    serialPort->print(className);
    serialPort->print("::");
    serialPort->print(methodName);
    serialPort->print("> ");
    serialPort->println(message);
  }
}

void DebugLogger::printf(const char *className, const char *methodName,
                         const char *format, ...) {

  if (serialPort) {
    char buffer[256]; // バッファサイズを設定
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format,
              args); // フォーマットされた文字列を作成
    va_end(args);

    print(className, methodName, buffer); // logメソッドを呼び出す
  }
}
