#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <Arduino.h>
#include <Stream.h>

class DebugLogger {
public:
  // シリアルポートの初期化
  static void init(HardwareSerial &serialPort, long baudRate = 9600);

  // デバッグメッセージを出力する
  static void print(const char *className, const char *methodName,
                    const char *message);

  // フォーマットされたデバッグメッセージを出力する
  static void printf(const char *className, const char *methodName,
                     const char *format, ...);

private:
  static HardwareSerial *serialPort; // シリアルポートを静的メンバーとして保持する
};

// マクロを定義して、簡単にログ出力できるようにする
#define LOG(className, methodName, message)                                    \
  DebugLogger::print(className, methodName, message)

#define LOGF(className, methodName, format, ...)                               \
  DebugLogger::printf(className, methodName, format, ##__VA_ARGS__)

#endif // DEBUG_LOGGER_H
