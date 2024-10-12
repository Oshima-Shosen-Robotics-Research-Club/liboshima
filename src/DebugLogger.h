#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/// ログレベルを定義する列挙型
/**
 * @enum DebugLoggerLevel
 * @brief ログメッセージの重要度を示す列挙型
 *
 * この列挙型は、ログメッセージの重要度を示します。
 * 各レベルは、情報メッセージ、警告メッセージ、エラーメッセージを表します。
 */
enum class DebugLoggerLevel : uint8_t {
  INFO, ///< 情報メッセージ
  WARN, ///< 警告メッセージ
  ERROR ///< エラーメッセージ
};

/// 待機モードを定義する列挙型
/**
 * @enum DebugLoggerMode
 * @brief ログメッセージの出力時の待機モードを示す列挙型
 *
 * この列挙型は、ログメッセージの出力時にデータが利用可能になるまで待機するかどうかを示します。
 * WAITモードはデータが利用可能になるまで待機し、NO_WAITモードはデータが利用できない場合は即座に終了します。
 */
enum class DebugLoggerMode : uint8_t {
  WAIT,   ///< データが利用可能になるまで待機
  NO_WAIT ///< データが利用できない場合は即座に終了
};

/**
 * @class DebugLogger
 * @brief デバッグメッセージをシリアルポートに出力するテンプレートクラス
 *
 * `SerialType` 型のオブジェクトにデバッグメッセージを出力するためのクラスです。
 * 典型的には、Arduinoや組み込みシステムのシリアルポート（例えば
 * `Serial`）を使用して、
 * クラス名、メソッド名、およびメッセージをシリアルポートに送信します。
 *
 * @tparam SerialType
 * シリアルポートクラスの型を指定します。例：`HardwareSerial`（Arduinoの場合）
 */
template <typename SerialType> class DebugLogger {
public:
  /**
   * @brief コンストラクタ
   *
   * `DebugLogger`
   * クラスのインスタンスを生成し、指定されたシリアルポートへの参照を保持します。
   *
   * @param serial デバッグメッセージを出力するシリアルポートへの参照
   * @param logLevel ログレベル（デフォルトはINFO）
   */
  DebugLogger(SerialType &serial,
              DebugLoggerLevel logLevel = DebugLoggerLevel::INFO)
      : serial(serial), logLevel(logLevel) {}

  /**
   * @brief シリアルポートを初期化するメソッド
   *
   * 指定したボーレートでシリアルポート通信を開始します。
   * デフォルトのボーレートは19200bpsです。
   *
   * @param baudrate シリアル通信のボーレート（デフォルトは19200）
   */
  void begin(unsigned long baudrate = 19200) { serial.begin(baudrate); }

  /**
   * @brief クラス名、メソッド名、およびメッセージを出力するメソッド
   *
   * デバッグメッセージとして、クラス名、メソッド名、およびメッセージをシリアルポートに出力します。
   *
   * @param className クラス名を示す文字列
   * @param methodName メソッド名を示す文字列
   * @param message デバッグメッセージを示す文字列
   * @param level ログレベル
   * @param wait データが利用可能になるまで待機するかどうか（デフォルトはWAIT）
   */
  void println(DebugLoggerLevel level, DebugLoggerMode wait,
               const char *className, const char *methodName,
               const char *message) {
    // 現在のログレベルが指定されたレベルよりも高い場合、メッセージを出力しない
    if (logLevel > level) {
      return;
    }

    // データが利用可能になるまで待機するか、即座に終了するかを決定
    if (wait == DebugLoggerMode::WAIT) {
      while (!serial.availableForWrite())
        ; // データが利用可能になるまで待機
    } else if (wait == DebugLoggerMode::NO_WAIT &&
               !serial.availableForWrite()) {
      return; // データが利用できない場合は即座に終了
    }

    // メッセージをシリアルポートに出力
    serial.print("<");
    serial.print(className);
    serial.print("::");
    serial.print(methodName);
    serial.print("> ");
    serial.println(message); // メッセージを出力
  }

  /**
   * @brief フォーマットされた文字列を出力するメソッド
   *
   * printf形式でメッセージをフォーマットし、クラス名、メソッド名と共にシリアルポートに出力します。
   *
   * @param className クラス名を示す文字列
   * @param methodName メソッド名を示す文字列
   * @param format 出力するメッセージのフォーマット文字列（printf形式）
   * @param level ログレベル
   * @param wait データが利用可能になるまで待機するかどうか（デフォルトはWAIT）
   * @param ... フォーマットする可変引数
   */
  void printlnf(DebugLoggerLevel level, DebugLoggerMode wait,
                const char *className, const char *methodName,
                const char *format, ...) {
    char buffer[100]; // 出力メッセージを格納するバッファサイズ
    va_list args;
    va_start(args, format); // 可変引数の初期化
    // フォーマットされた文字列を作成
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args); // 可変引数の解放
    // フォーマットされたメッセージを出力
    println(level, wait, className, methodName, buffer);
  }

private:
  /// デバッグメッセージを出力するシリアルポートへの参照
  SerialType &serial;
  /// 現在のログレベル
  DebugLoggerLevel logLevel;
};