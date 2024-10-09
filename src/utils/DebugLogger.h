/**
 * @file DebugLogger.h
 * @brief シリアルポートにデバッグメッセージを出力するテンプレートクラス
 *
 * このファイルは、デバッグ用のメッセージをシリアルポートに出力するための
 * `DebugLogger` テンプレートクラスを提供します。
 * 任意のシリアルポートクラスをテンプレートパラメータとして受け取り、可変長引数を使用して
 * フォーマットされたメッセージを出力することが可能です。
 */

#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

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
   */
  DebugLogger(SerialType &serial) : serial(serial) {}

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
   */
  void println(const char *className, const char *methodName,
               const char *message) {
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
   * @param ... フォーマット文字列に埋め込む可変引数
   */
  void printlnf(const char *className, const char *methodName,
                const char *format, ...) {
    char buffer[100]; // 出力メッセージを格納するバッファサイズ
    va_list args;
    va_start(args, format); // 可変引数の初期化
    vsnprintf(buffer, sizeof(buffer), format,
              args); // フォーマットされた文字列を作成
    va_end(args);    // 可変引数の解放
    println(className, methodName,
            buffer); // フォーマットされたメッセージを出力
  }

  /**
   * @brief クラス名、メソッド名、およびメッセージを出力するメソッド（待機）
   *
   * シリアルポートが利用可能になるまで待機し、デバッグメッセージを出力します。
   *
   * @param className クラス名を示す文字列
   * @param methodName メソッド名を示す文字列
   * @param message デバッグメッセージを示す文字列
   */
  void printlnWait(const char *className, const char *methodName,
                   const char *message) {
    while (!serial.availableForWrite())
      ;
    println(className, methodName, message);
  }

  /**
   * @brief フォーマットされた文字列を出力するメソッド（待機）
   *
   * シリアルポートが利用可能になるまで待機し、フォーマットされたメッセージを出力します。
   *
   * @param className クラス名を示す文字列
   * @param methodName メソッド名を示す文字列
   * @param format 出力するメッセージのフォーマット文字列（printf形式）
   * @param ... フォーマット文字列に埋め込む可変引数
   */
  void printlnfWait(const char *className, const char *methodName,
                    const char *format, ...) {
    while (!serial.availableForWrite())
      ;
    char buffer[100]; // 出力メッセージを格納するバッファサイズ
    va_list args;
    va_start(args, format); // 可変引数の初期化
    // フォーマットされた文字列を作成
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args); // 可変引数の解放
    // フォーマットされたメッセージを出力
    println(className, methodName, buffer);
  }

private:
  /// デバッグメッセージを出力するシリアルポートへの参照
  SerialType &serial;
};
