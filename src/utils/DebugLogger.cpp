#include "DebugLogger.h"
#include <SoftwareSerial.h>
#include <stdarg.h>
#include <stdio.h>

// DebugLoggerクラスの静的メンバーの初期化
Stream *DebugLogger::serialPort = nullptr;

// シリアルポートを初期化するメソッド
// ハードウェアシリアルポートを指定して初期化する
void DebugLogger::init(HardwareSerial &serial, unsigned long baudrate) {
  // 既にシリアルポートが初期化されている場合は何もしない
  if (serialPort) {
    return;
  }
  serial.begin(baudrate);
  serialPort = &serial;
}

// シリアルポートを初期化するメソッド
// ソフトウェアシリアルポートを指定して初期化する
void DebugLogger::init(SoftwareSerial &serial, unsigned long baudrate) {
  // 既にシリアルポートが初期化されている場合は何もしない
  if (serialPort) {
    return;
  }
  serial.begin(baudrate);
  serialPort = &serial;
}

// シリアルポートを初期化するメソッド
// RXピン、TXピン、ボーレートを指定して初期化する
void DebugLogger::init(uint8_t rxPin, uint8_t txPin, unsigned long baudrate) {
  // 既にシリアルポートが初期化されている場合は何もしない
  if (serialPort) {
    return;
  }
  SoftwareSerial *serial = new SoftwareSerial(rxPin, txPin);
  serial->begin(baudrate);
  serialPort = serial;
}

// ログメッセージを出力するメソッド
// クラス名、メソッド名、メッセージを指定して出力する
void DebugLogger::println(const char *className, const char *methodName,
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

// フォーマットされたログメッセージを出力するメソッド
// クラス名、メソッド名、フォーマット、可変引数を指定して出力する
void DebugLogger::printlnf(const char *className, const char *methodName,
                           const char *format, ...) {
  if (serialPort) {
    char buffer[256]; // バッファサイズを設定
    va_list args;
    va_start(args, format);
    // フォーマットされた文字列を作成
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    println(className, methodName, buffer); // printlnメソッドを呼び出す
  }
}
