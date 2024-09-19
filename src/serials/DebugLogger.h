#pragma once

#ifdef DEBUG

#include <stdarg.h>
#include <stdio.h>

/**
 * @brief デバッグメッセージをシリアルポートに出力するテンプレートクラス
 *
 * `DebugLogger` テンプレートクラスは、任意の `Stream`
 * を使用してデバッグメッセージを出力するメソッドを提供します。
 * シンプルなメッセージやフォーマットされたメッセージの出力がサポートされています。
 *
 * デバッグメッセージを出力するためには、`DEBUG` マクロを定義し、`init`
 * メソッドを呼び出してシリアルポートを初期化する必要があります。
 */
template <typename T> class DebugLogger {
public:
  /**
   * @brief 任意の `Stream` で `DebugLogger` を初期化します。
   *
   * @param serial ログ出力に使用する `Stream` オブジェクト（例: Serial,
   * SoftwareSerial など）。
   * @param baudrate シリアル通信速度（ボーレート）。デフォルト値は9600。
   */
  static void init(T &serial, unsigned long baudrate = 9600) {
    // 既にシリアルポートが初期化されている場合は何もしない
    if (serialPort) {
      return;
    }
    serialPort = &serial;
  }

  /**
   * @brief シンプルなデバッグメッセージをシリアルポートに出力します。
   *
   * @param className ログが呼び出されるクラスの名前。
   * @param methodName ログが呼び出されるメソッドの名前。
   * @param message 出力するデバッグメッセージ。
   */
  static void println(const char *className, const char *methodName,
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

  /**
   * @brief フォーマットされたデバッグメッセージをシリアルポートに出力します。
   *
   * @param className ログが呼び出されるクラスの名前。
   * @param methodName ログが呼び出されるメソッドの名前。
   * @param format メッセージのフォーマット文字列（printf 形式）。
   * @param ... メッセージをフォーマットするための可変引数。
   */
  static void printlnf(const char *className, const char *methodName,
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

private:
  /**
   * @brief ログ出力に使用するシリアルポートへの静的ポインタ。
   */
  static T *serialPort;
};

// 静的メンバー変数の定義
template <typename T> T *DebugLogger<T>::serialPort = nullptr;

// デバッグメッセージを簡単に出力するためのマクロを定義します。
#define LOG(className, methodName, message)                                    \
  DebugLogger<Stream>::println(className, methodName, message)

/**
 * @brief フォーマットされたデバッグメッセージを簡単に出力するためのマクロ。
 *
 * @param className ログが呼び出されるクラスの名前。
 * @param methodName ログが呼び出されるメソッドの名前。
 * @param format メッセージのフォーマット文字列（printf 形式）。
 * @param ... メッセージをフォーマットするための可変引数。
 */
#define LOGF(className, methodName, format, ...)                               \
  DebugLogger<Stream>::printlnf(className, methodName, format, ##__VA_ARGS__)

#else // DEBUG is not defined
template <typename T> class DebugLogger {
public:
  static inline void init(T &, unsigned long baudrates) {}

  static inline void println(const char *, const char *, const char *) {}
  static inline void printlnf(const char *, const char *, const char *, ...) {}
};

#define LOG(className, methodName, message) (void)0
#define LOGF(className, methodName, format, ...) (void)0

#endif // DEBUG
