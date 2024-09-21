#pragma once

#include <Arduino.h>
#include <serials/SerialPort.h>

#if defined(DEBUG)
/**
 * @brief デバッグメッセージをシリアルポートに出力するクラス
 *
 * `DebugLogger`クラスは、ハードウェアまたはソフトウェアのシリアルポートにデバッグメッセージを出力するためのメソッドを提供します。
 * シンプルなメッセージやフォーマットされたメッセージの出力がサポートされています。
 *
 * デバッグメッセージを出力するためには、`DEBUG`マクロを定義し、`init`メソッドを呼び出してシリアルポートを初期化する必要があります。
 */
class DebugLogger {
public:
  /**
   * @brief ハードウェアシリアルポートで `DebugLogger` を初期化します。
   *
   * @param serial ログ出力に使用するハードウェアシリアルポート（例: Serial）。
   * @param baudrate シリアル通信のボーレート（デフォルトは 19200）。
   */
  void init(SerialPort &serial, unsigned long baudrate = 19200);

  /**
   * @brief シンプルなデバッグメッセージをシリアルポートに出力します。
   *
   * @param className ログが呼び出されるクラスの名前。
   * @param methodName ログが呼び出されるメソッドの名前。
   * @param message 出力するデバッグメッセージ。
   */
  void println(const char *className, const char *methodName,
               const char *message);

  /**
   * @brief フォーマットされたデバッグメッセージをシリアルポートに出力します。
   *
   * @param className ログが呼び出されるクラスの名前。
   * @param methodName ログが呼び出されるメソッドの名前。
   * @param format メッセージのフォーマット文字列（printf 形式）。
   * @param ... メッセージをフォーマットするための可変引数。
   */
  void printlnf(const char *className, const char *methodName,
                const char *format, ...);

private:
  /**
   * @brief ログ出力に使用するシリアルポートへのポインタ。
   */
  SerialPort *serialPort;
};

#else // DEBUG is not defined
class DebugLogger {
public:
  void init(SerialPort &serial, unsigned long baudrate = 19200) {}
  void println(const char *className, const char *methodName,
               const char *message) {}
  void printlnf(const char *className, const char *methodName,
                const char *format, ...) {}
};

#endif // DEBUG

extern DebugLogger Logger; ///< グローバルインスタンスの宣言