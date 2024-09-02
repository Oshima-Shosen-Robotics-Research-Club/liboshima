#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <Arduino.h>
#include <Stream.h>

// DebugLoggerクラスの定義
class DebugLogger {
public:
  // シリアルポートの初期化
  // 指定されたシリアルポートとボーレートで初期化する
  static void init(HardwareSerial &serialPort, long baudRate = 19200);

  // デバッグメッセージを出力する
  // クラス名、メソッド名、メッセージを指定して出力する
  static void print(const char *className, const char *methodName,
                    const char *message);

  // フォーマットされたデバッグメッセージを出力する
  // クラス名、メソッド名、フォーマット、可変引数を指定して出力する
  static void printf(const char *className, const char *methodName,
                     const char *format, ...);

private:
  // シリアルポートを静的メンバーとして保持する
  static HardwareSerial *serialPort;
};

// マクロを定義して、簡単にログ出力できるようにする
#define LOG(className, methodName, message)                                    \
  DebugLogger::print(className, methodName, message)

#define LOGF(className, methodName, format, ...)                               \
  DebugLogger::printf(className, methodName, format, ##__VA_ARGS__)

#endif // DEBUG_LOGGER_H