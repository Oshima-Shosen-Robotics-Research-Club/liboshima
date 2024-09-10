#include "DebugLogger.h"
#include <stdarg.h>
#include <stdio.h>

// DebugLoggerクラスの静的メンバーの初期化
Stream *DebugLogger::serialPort = nullptr;

// DebugLoggerの初期化メソッド
// 指定されたシリアルポートを初期化する
void DebugLogger::init(Stream &port) {
  serialPort = &port;
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
