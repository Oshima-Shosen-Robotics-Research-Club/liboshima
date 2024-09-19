/**
 * @file ImReceiver.h
 * @brief IM920SL通信モジュールを用いたデータ受信のためのクラス定義
 *
 * このファイルには、IM920SL通信モジュールを用いてデータを受信するための
 * `ImReceiver` クラスが定義されています。`ImReceiver`
 * クラスは、任意のシリアルインターフェース型（`HardwareSerial`、`SoftwareSerial`など）
 * と連携してデータを受信し、受信したデータを指定した
 * 型に変換する機能を提供します。
 *
 * @note このクラスは、テンプレートメソッドを使用して様々な型のデータを
 *       受信することができます。
 */

#pragma once

#include "serials/DebugLogger.h"
#include <SoftwareSerial.h>

// タイマーオーバーフローに最適な時間間隔 (ミリ秒単位)
// この定義は受信タイミングの調整に使用される可能性があります。
// ユーザーが調整することで、受信間隔を制御できます。
#define IM_RECEIVE_INTERVAL_MILLIS 500

// タイマーオーバーフローに最適な時間間隔 (マイクロ秒単位)
// この定義は受信タイミングの調整に使用される可能性があります。
// ユーザーが調整することで、受信間隔を制御できます。
#define IM_RECEIVE_INTERVAL_MICROS 500000

// バイナリのサイズは大きくなるが、処理が増えるわけではないので、問題ないと考える
/*
'0' = 48, '9' = 57, 'A' = 65, 'F' = 70
*/
constexpr uint8_t lookup[] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
    34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, // パディング
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,                  // 0-9
    58, 59, 60, 61, 62, 63, 64,                             // パディング
    10, 11, 12, 13, 14, 15,                                 // A-F
};

/**
 * @class ImReceiver
 * @brief IM920SL通信モジュールを用いたデータ受信を行うクラス
 *
 * `ImReceiver` クラスは、IM920SL通信モジュールを使用してデータを受信し、
 * 受信したデータを指定した型に変換するための機能を提供します。このクラスは
 * 任意のシリアルインターフェース型と連携し、テンプレートメソッドを
 * 使用してさまざまな型のデータを受信することができます。
 */
template <typename T> class ImReceiver {
public:
  /**
   * @brief コンストラクタ
   *
   * 任意のシリアルインターフェース型のインスタンスを使用して通信を行います。
   *
   * @param serial 使用するシリアルインターフェース型インスタンスの参照
   * @param baudrate 通信速度（ボーレート）。デフォルト値は19200。
   */
  ImReceiver(T &serial, unsigned long baudrate = 19200) : serial(serial) {
    serial.begin(baudrate);
  }

#ifdef DEBUG
  /**
   * @enum ErrorCode
   * @brief エラーコードの列挙型
   *
   * `ImReceiver` クラスで発生する可能性のあるエラーコードを定義します。
   */
  enum class ErrorCode {
    SUCCESS, /**< データ受信が成功したことを示します。 */
    NO_DATA_AVAILABLE, /**< データが利用可能でないことを示します。 */
    RECEIVED_STRING_LENGTH_INVALID, /**<
                                       受信文字列の長さが無効であることを示します。
                                     */
    COLON_NOT_FOUND, /**< 文字列内にコロンが見つからないことを示します。 */
    DATA_STRING_INVALID, /**< データ文字列が無効であることを示します。*/
  };
#endif

  /**
   * @brief データが利用可能かどうかをチェックするメソッド
   *
   * このメソッドは、受信バッファにデータが利用可能かどうかを確認します。
   *
   * @return データが利用可能であれば `true`、そうでなければ `false`
   * を返します。
   */
  bool available() { return serial.available(); }

  /**
   * @brief データを受信するテンプレートメソッド
   *
   * このメソッドは、テンプレート型 `T` のデータを受信し、指定された型に
   * 変換します。サポートされる型は `int` 型、`float` 型、構造体などの
   * 直接値を保持する型に限定されています。
   *
   * @tparam U 受信するデータの型
   * @param data 受信したデータを格納する変数の参照
   * @return データ受信の結果を示す `ErrorCode`
   *
   * @note 受信データはコロン `:` で区切られた形式であると想定しています。
   *       受信文字列の長さが予期される長さと一致しない場合や、データの
   *       長さが無効である場合は、エラーコードが返されます。
   */
  template <typename U>
// "00,0000,00:00,00,00\r\n" という形式のデータを受信する
#ifdef DEBUG
  ErrorCode
#else
  void
#endif
  receive(U &data) {
    DebugLogger::println("ImReceiver", "receive", "Receiving data");

#ifdef DEBUG
    // データが利用可能でない場合はエラーを返す
    if (!available()) {
      DebugLogger::println("ImReceiver", "receive", "No data available");
      return ErrorCode::NO_DATA_AVAILABLE;
    }
#endif

    // 受信データの読み取り
    // 最大32バイトのデータを受信する
    // "00,0000,00:01,02,03,04,05,06,07,08,09,0A,0B,0C,0D,0E,0F,10,11,12,13,14,15,16,17,18,19,1A,1B,1C,1D,1E,1F,20"
    // ペイロード = 10、コロン = 1、データ = 32 * 2、カンマ = 32 - 1 = 31
    char recvedStr[10 + 1 + 32 * 2 + 31 + 1]; // null文字を含める
    size_t length =
        serial.readBytesUntil('\n', recvedStr, sizeof(recvedStr) - 1);
    recvedStr[length] = '\0'; // Null-terminate the string

    // 受信文字をデバッグ出力
    DebugLogger::printlnf("ImReceiver", "receive", "Received: %s", recvedStr);

#ifdef DEBUG
    // 受信文字列の長さが予期される長さと一致しない場合はエラーを返す
    if (length != 10 + 1 + sizeof(U) * 2 + sizeof(U) - 1) {
      DebugLogger::println("ImReceiver", "receive",
                           "Received string length invalid");
      return ErrorCode::RECEIVED_STRING_LENGTH_INVALID;
    }

    if (recvedStr[10] != ':') {
      DebugLogger::println("ImReceiver", "receive", "Colon not found");
      return ErrorCode::COLON_NOT_FOUND;
    }
#endif

    // データ部分のみを抽出
    char *pos = recvedStr + 11;

#ifdef DEBUG
    // 無効な文字列が含まれている場合はエラーを返す
    if (!((pos[0] >= '0' && pos[0] <= '9') ||
          (pos[0] >= 'A' && pos[0] <= 'F')) ||
        !((pos[1] >= '0' && pos[1] <= '9') ||
          (pos[1] >= 'A' && pos[1] <= 'F'))) {
      DebugLogger::println("ImReceiver", "receive", "Data string invalid");
      return ErrorCode::DATA_STRING_INVALID;
    }
#endif

    for (size_t i = 0; i < sizeof(U); i++) {
      uint8_t high = lookup[(uint8_t)*pos++];
      uint8_t low = lookup[(uint8_t)*pos++];

      ((uint8_t *)data)[i] = (high << 4) | low;

      if (*pos == ',') {
        pos++;
      }
    }

    // データをデバッグ出力
    DebugLogger::println("ImReceiver", "receive", "Data received");

#ifdef DEBUG
    return ErrorCode::SUCCESS;
#endif
  }

private:
  T &serial; /**< データ受信に使用するシリアル通信オブジェクト */
};