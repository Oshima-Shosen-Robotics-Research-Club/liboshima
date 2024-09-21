#include "utils/DebugLogger.h"

#if defined(DEBUG)

DebugLogger Debug; ///< グローバルインスタンスの定義
SerialPort *DebugLogger::serialPort = nullptr; ///< ポインタの初期化

void DebugLogger::init(SerialPort &serial, unsigned long baudrate) {
  if (serialPort) {
    return; // 既に初期化されている場合は何もしない
  }
  serial.begin(baudrate); // シリアルポートを開始
  serialPort = &serial;   // ポインタを設定
}

void DebugLogger::println(const char *className, const char *methodName,
                          const char *message) {
  if (serialPort) {
    serialPort->print("<");
    serialPort->print(className);
    serialPort->print("::");
    serialPort->print(methodName);
    serialPort->print("> ");
    serialPort->println(message); // メッセージを出力
  }
}

void DebugLogger::printlnf(const char *className, const char *methodName,
                           const char *format, ...) {
  if (serialPort) {
    char buffer[100]; // バッファサイズを設定
    va_list args;
    va_start(args, format); // 可変引数の初期化
    vsnprintf(buffer, sizeof(buffer), format,
              args); // フォーマットされた文字列を作成
    va_end(args);    // 可変引数の解放
    println(className, methodName, buffer); // printlnメソッドを呼び出す
  }
}

#endif // DEBUG
