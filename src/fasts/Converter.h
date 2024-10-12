/**
 * @file Converter.h
 * @brief バイナリデータと16進数表現の相互変換を行うクラス
 *
 * `Converter` クラスは、バイトデータを16進数表現に変換したり、
 * 16進数表現からバイトデータに変換する機能を提供します。
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * @class Converter
 * @brief バイナリデータと16進数表現の相互変換を行うユーティリティクラス
 *
 * `Converter` クラスは、データを16進数表現に変換する静的メソッドや、
 * 16進数表現から元のバイトデータに変換するメソッドを提供します。
 */
class Converter {
public:
  /**
   * @brief バイトデータを16進数表現に変換します。
   *
   * 指定されたバイトデータを16進数表現に変換し、出力バッファに格納します。
   * 各バイトは2文字の16進数表現に変換されます。
   *
   * @param data 変換するバイトデータのポインタ
   * @param length バイトデータの長さ
   * @param output 変換後の16進数文字列を格納するバッファ（null終端文字を含めた十分なサイズが必要です）
   *
   * @note `output` バッファのサイズは `length * 2 + 1` バイト必要です。
   */
  static void toHex(const uint8_t *data, size_t length, char *output);

  /**
   * @brief 16進数表現からバイトデータに変換します。
   *
   * 指定された16進数文字列をバイトデータに変換し、出力バッファに格納します。
   * 各2文字の16進数表現が1バイトに変換されます。
   *
   * @param hexString 変換する16進数文字列のポインタ
   * @param length 16進数文字列の長さ（2の倍数でなければなりません）
   * @param output 変換後のバイトデータを格納するバッファ
   *
   * @note `length` は偶数でなければなりません。奇数の場合の動作は未定義です。
   */
  static void fromHex(const char *hexString, size_t length, uint8_t *output);

private:
  /**
   * @brief 16進数文字に対応する数値を取得するためのルックアップテーブル
   *
   * '0'-'9' 及び 'A'-'F' を対応する16進数の値に変換するためのテーブルです。
   */
  static const char hexLookup[16];

  /**
   * @brief 16進数文字列の各文字を数値に変換するためのルックアップテーブル
   *
   * '0'-'9' と 'A'-'F' を、それぞれ対応する数値に変換するためのテーブルです。
   */
  static const uint8_t valueLookup[23];
};