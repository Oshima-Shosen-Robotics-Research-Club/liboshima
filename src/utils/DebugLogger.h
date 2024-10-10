#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/// ログレベルを定義する列挙型を持つ共通ベースクラス
class DebugLoggerBase {
public:
  /// ログレベルを定義する列挙型
  enum class LogLevel : uint8_t {
    INFO, ///< 情報メッセージ
    WARN, ///< 警告メッセージ
    ERROR ///< エラーメッセージ
  };

  /// 待機モードを定義する列挙型
  enum class WaitMode : uint8_t {
    WAIT,   ///< データが利用可能になるまで待機
    NO_WAIT ///< データが利用できない場合は即座に終了
  };
};

/**
 * @class DebugLogger
 * @brief デバッグメッセージをシリアルポートに出力するテンプレートクラス
 *
 * `SerialType` 型のオブジェクトにデバッグメッセージを出力するためのクラスです。
 * 典型的には、Arduinoや組み込みシステムのシリアルポート（例えば
 * `Serial`）を使用して、クラス名、メソッド名、およびメッセージをシリアルポートに送信します。
 *
 * @tparam SerialType
 * シリアルポートクラスの型を指定します。例：`HardwareSerial`（Arduinoの場合）
 */
template <typename SerialType> class DebugLogger : public DebugLoggerBase {
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
  DebugLogger(SerialType &serial, LogLevel logLevel = LogLevel::INFO)
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
  void println(LogLevel level, WaitMode wait, const char *className,
               const char *methodName, const char *message) {
    if (logLevel > level) {
      return;
    }

    if (wait == WaitMode::WAIT) {
      while (!serial.availableForWrite())
        ;
    } else if (wait == WaitMode::NO_WAIT && !serial.availableForWrite()) {
      return;
    }

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
  void printlnf(LogLevel level, WaitMode wait, const char *className,
                const char *methodName, const char *format, ...) {
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
  LogLevel logLevel; ///< ログレベル
};

template <> class DebugLogger<void> : public DebugLoggerBase {};