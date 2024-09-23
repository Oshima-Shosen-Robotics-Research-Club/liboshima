#pragma once

#include <Arduino.h>
#include <serials/SerialPort.h>

#if defined(DEBUG)
/**
 * @class DebugLogger
 * @brief デバッグメッセージをシリアルポートに出力するクラス
 *
 * `DebugLogger`
 * クラスは、ハードウェアまたはソフトウェアのシリアルポートを使用して、デバッグメッセージを出力するための機能を提供します。
 * クラス名やメソッド名を指定してシンプルなログメッセージやフォーマットされたメッセージを出力することができます。
 *
 * このクラスのメソッドは `DEBUG` マクロが定義されている場合にのみ機能します。
 */
class DebugLogger {
public:
  /**
   * @brief シリアルポートで `DebugLogger` を初期化します。
   *
   * このメソッドは、指定されたシリアルポートとボーレートを使ってログの出力を行う準備をします。
   *
   * @param serial ログ出力に使用する `SerialPort` インスタンス（例:
   * `Serial`）。
   * @param baudrate シリアル通信のボーレート（デフォルトは 19200）。
   */
  void init(SerialPort &serial, unsigned long baudrate = 19200);

  /**
   * @brief シンプルなデバッグメッセージを出力します。
   *
   * このメソッドは、指定されたクラス名、メソッド名、メッセージをシリアルポートに出力します。
   * デバッグ用にシンプルなメッセージを提供したい場合に使用します。
   *
   * @param className 呼び出し元クラスの名前。
   * @param methodName 呼び出し元メソッドの名前。
   * @param message 出力するデバッグメッセージ。
   */
  void println(const char *className, const char *methodName,
               const char *message);

  /**
   * @brief フォーマットされたデバッグメッセージを出力します。
   *
   * このメソッドは、指定されたクラス名、メソッド名と共に、可変引数を使用してフォーマットされたメッセージをシリアルポートに出力します。
   * `printf`
   * 形式でメッセージを指定できるため、動的な内容を含むメッセージを出力する際に便利です。
   *
   * @param className 呼び出し元クラスの名前。
   * @param methodName 呼び出し元メソッドの名前。
   * @param format メッセージのフォーマット文字列（`printf` 形式）。
   * @param ... メッセージのフォーマットに使用する可変引数。
   */
  void printlnf(const char *className, const char *methodName,
                const char *format, ...);

private:
  /**
   * @brief ログの出力に使用するシリアルポートへのポインタ。
   */
  SerialPort *serialPort;
};

#else // DEBUG is not defined
/**
 * @class DebugLogger
 * @brief デバッグモードが無効な場合のダミークラス
 *
 * `DEBUG`
 * が定義されていない場合、このクラスは機能しないダミーメソッドを持ち、パフォーマンスへの影響を最小限に抑えます。
 */
class DebugLogger {
public:
  /**
   * @brief ダミーの初期化メソッド
   *
   * `DEBUG` が定義されていない場合、このメソッドは何もしません。
   */
  void init(SerialPort &serial, unsigned long baudrate = 19200) {}

  /**
   * @brief ダミーのメッセージ出力メソッド
   *
   * `DEBUG` が定義されていない場合、このメソッドは何もしません。
   */
  void println(const char *className, const char *methodName,
               const char *message) {}

  /**
   * @brief ダミーのフォーマットメッセージ出力メソッド
   *
   * `DEBUG` が定義されていない場合、このメソッドは何もしません。
   */
  void printlnf(const char *className, const char *methodName,
                const char *format, ...) {}
};

#endif // DEBUG

/**
 * @brief グローバル `DebugLogger` インスタンス
 *
 * プロジェクト全体で使用するデフォルトの `DebugLogger` インスタンス。
 * `DEBUG` が有効な場合にログを出力します。
 */
extern DebugLogger Logger;
