#include "DebugLogger.h"
#include <SoftwareSerial.h>
#include <stdarg.h>
#include <stdio.h>

// DebugLoggerクラスの静的メンバーの初期化
Stream *DebugLogger::serialPort = nullptr;

// シリアルポートを初期化するメソッド
void DebugLogger::init(int rxPin, int txPin, bool isSoftwareSerial,
                       unsigned long baudrate) {
  if (serialPort) {
    // 既にシリアルポートが初期化されている場合は何もしない
    return;
  }

  if (isSoftwareSerial) {
    // ソフトウェアシリアルを使用する場合
    SoftwareSerial *softSerial = new SoftwareSerial(rxPin, txPin);
    softSerial->begin(baudrate);
    serialPort = softSerial;
  } else {
    // ハードウェアシリアルを使用する場合
    Serial.begin(baudrate);
    serialPort = &Serial;
  }
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
