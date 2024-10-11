/**
 * @file FastwareSerial.h
 * @brief 高速シリアル通信を行うためのクラス FastwareSerial の宣言
 *
 * FastwareSerial クラスは、効率的なシリアル通信をサポートし、標準的なシリアル通信機能に加えて
 * ユーザー定義の受信イベントハンドラもサポートします。
 * ！注意！：現時点では正常に機能しません。（だれかよろしくお願いします）
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * @class FastwareSerial
 * @brief 高速シリアル通信を提供するクラス
 *
 * FastwareSerial クラスは、標準的なシリアル通信機能を提供し、データの送受信、バッファの確認、
 * およびユーザー定義の受信イベントハンドラをサポートします。
 */
class FastwareSerial {
public:
  /**
   * @brief シリアル通信の初期化を行います。
   * @param baudrate シリアル通信のボーレート（通信速度）
   */
  void begin(unsigned long baudrate);

  /**
   * @brief 受信バッファに格納されている利用可能なデータのバイト数を取得します。
   * @return 利用可能なデータのバイト数
   */
  uint8_t available();

  /**
   * @brief 1バイトのデータを読み取ります。
   * @return 読み取られたデータ（1バイト）
   */
  char read();

  /**
   * @brief 指定した終端文字までのデータを読み取り、バッファに格納します。
   *
   * 指定した終端文字に到達するか、バッファが一杯になるまでデータを読み取ります。
   *
   * @param terminator 読み取りを終了する終端文字
   * @param buffer 読み取ったデータを格納するバッファ
   * @param length バッファの長さ（最大読み取りバイト数）
   * @return 実際に読み取られたバイト数
   */
  uint8_t readBytesUntil(char terminator, char *buffer, uint8_t length);

  /**
   * @brief 1バイトのデータを送信します。
   * @param data 送信するデータ（1バイト）
   * @return 送信に成功した場合は 1、失敗した場合は 0
   */
  uint8_t write(uint8_t data);

  /**
   * @brief 文字列を送信します。
   * @param str 送信する文字列
   * @return 送信に成功したバイト数
   */
  uint8_t print(const char *str);

  /**
   * @brief 数値データを文字列として送信します。
   * @param value 送信する数値
   * @return 送信に成功したバイト数
   */
  uint8_t print(uint8_t value);

  /**
   * @brief 文字列を送信し、改行を付加します。
   * @param str 送信する文字列
   * @return 送信に成功したバイト数
   */
  uint8_t println(const char *str);

  /**
   * @brief 改行のみを送信します。
   * @return 送信に成功したバイト数
   */
  uint8_t println();

  /**
   * @brief データ受信時に呼び出される関数を登録します。
   * @param function データ受信時に実行されるコールバック関数
   */
  void onReceive(void (*function)(void));

  /**
   * @brief ユーザーが登録した受信イベントハンドラ
   *
   * `onReceive` メソッドで設定された、データ受信時に呼び出されるコールバック関数です。
   */
  void (*user_onReceive)(void);
};

/**
 * @brief グローバルな FastwareSerial インスタンス
 *
 * シリアル通信のための標準的な `FastwareSerial` インスタンス。
 */
extern FastwareSerial FastSerial;