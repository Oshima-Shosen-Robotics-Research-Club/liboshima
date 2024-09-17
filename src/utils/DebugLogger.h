#ifndef DEBUG_LOGGER_H
#define DEBUG_LOGGER_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Stream.h>

/**
 * @brief デバッグメッセージをシリアルポートに出力するクラス
 *
 * `DebugLogger`
 * クラスは、ハードウェアまたはソフトウェアのシリアルポートにデバッグメッセージを出力するためのメソッドを提供します。
 * シンプルなメッセージやフォーマットされたメッセージの出力がサポートされています。
 */
class DebugLogger {
public:
  /**
   * @brief ハードウェアシリアルポートで `DebugLogger` を初期化します。
   *
   * @param serial ログ出力に使用するハードウェアシリアルポート（例: Serial）。
   * @param baudrate シリアル通信のボーレート（デフォルトは 19200）。
   */
  static void init(HardwareSerial &serial, unsigned long baudrate = 19200);

  /**
   * @brief ソフトウェアシリアルポートで `DebugLogger` を初期化します。
   *
   * @param serial ログ出力に使用するソフトウェアシリアルポート。
   * @param baudrate シリアル通信のボーレート（デフォルトは 19200）。
   */
  static void init(SoftwareSerial &serial, unsigned long baudrate = 19200);

  /**
   * @brief ピン番号を使用してソフトウェアシリアルポートで `DebugLogger`
   * を初期化します。
   *
   * @param rxPin ソフトウェアシリアルポートの RX ピン番号。
   * @param txPin ソフトウェアシリアルポートの TX ピン番号。
   * @param baudrate シリアル通信のボーレート（デフォルトは 19200）。
   */
  static void init(uint8_t rxPin, uint8_t txPin,
                   unsigned long baudrate = 19200);

  /**
   * @brief シンプルなデバッグメッセージをシリアルポートに出力します。
   *
   * @param className ログが呼び出されるクラスの名前。
   * @param methodName ログが呼び出されるメソッドの名前。
   * @param message 出力するデバッグメッセージ。
   */
  static void println(const char *className, const char *methodName,
                      const char *message);

  /**
   * @brief フォーマットされたデバッグメッセージをシリアルポートに出力します。
   *
   * @param className ログが呼び出されるクラスの名前。
   * @param methodName ログが呼び出されるメソッドの名前。
   * @param format メッセージのフォーマット文字列（printf 形式）。
   * @param ... メッセージをフォーマットするための可変引数。
   */
  static void printlnf(const char *className, const char *methodName,
                       const char *format, ...);

private:
  /**
   * @brief ログ出力に使用するシリアルポートへの静的ポインタ。
   */
  static Stream *serialPort;
};

// デバッグメッセージを簡単に出力するためのマクロを定義します。
#define LOG(className, methodName, message)                                    \
  DebugLogger::println(className, methodName, message)

/**
 * @brief フォーマットされたデバッグメッセージを簡単に出力するためのマクロ。
 *
 * @param className ログが呼び出されるクラスの名前。
 * @param methodName ログが呼び出されるメソッドの名前。
 * @param format メッセージのフォーマット文字列（printf 形式）。
 * @param ... メッセージをフォーマットするための可変引数。
 */
#define LOGF(className, methodName, format, ...)                               \
  DebugLogger::printlnf(className, methodName, format, ##__VA_ARGS__)

#endif // DEBUG_LOGGER_H
