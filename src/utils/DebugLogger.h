#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <Arduino.h>
#include <Stream.h>

// DebugLoggerクラスの定義
class DebugLogger {
public:
  // シリアルポートの初期化
  // 指定されたシリアルポートを初期化する
  static void init(Stream &port, unsigned long baudrate = 19200);
  static void init(HardwareSerial &port, unsigned long baudrate = 19200);

  // デバッグメッセージを出力する
  // クラス名、メソッド名、メッセージを指定して出力する
  static void println(const char *className, const char *methodName,
                      const char *message);

  // フォーマットされたデバッグメッセージを出力する
  // クラス名、メソッド名、フォーマット、可変引数を指定して出力する
  static void printlnf(const char *className, const char *methodName,
                       const char *format, ...);

private:
  // シリアルポートを静的メンバーとして保持する
  static Stream *serialPort;
};

// マクロを定義して、簡単にログ出力できるようにする
#define LOG(className, methodName, message)                                    \
  DebugLogger::println(className, methodName, message)

#define LOGF(className, methodName, format, ...)                               \
  DebugLogger::printlnf(className, methodName, format, ##__VA_ARGS__)

#endif // DEBUG_LOGGER_H
