/**
 * @file ImSender.h
 * @brief IM920SL通信モジュールを用いたデータ送信のためのクラス定義
 *
 * このファイルには、IM920SL通信モジュールを用いてデータを送信するための
 * `ImSender` クラスが定義されています。`ImSender` クラスは、`HardwareSerial`
 * または `SoftwareSerial`
 * と連携してデータを送信するためのメソッドを提供します。
 *
 * @note
 * このクラスは、テンプレートを用いて様々なデータ型の送信をサポートします。
 */

#pragma once

#include "serials/DebugLogger.h"

// データ送信に適した時間間隔 (ミリ秒単位)
#define IM_SEND_INTERVAL 60

/**
 * @class ImSender
 * @brief IM920SL通信モジュールを用いたデータ送信を行うクラス
 *
 * `ImSender` クラスは、IM920SL通信モジュールを使用してデータを送信するための
 * 機能を提供します。このクラスは `HardwareSerial` または `SoftwareSerial` と
 * 連携し、テンプレートメソッドを使用して様々な型のデータを送信できます。
 */
template <typename SerialType> class ImSender {
public:
  /**
   * @brief コンストラクタ
   *
   * `SerialType` インスタンスを使用して通信を行います。
   *
   * @param serial 使用する `SerialType` インスタンスの参照
   * @param baudrate 通信速度（ボーレート）。デフォルト値は19200。
   */
  ImSender(SerialType &serial, unsigned long baudrate = 19200)
      : serial(serial) {
    serial.begin(baudrate);
  }

#ifdef DEBUG
  /**
   * @enum ErrorCode
   * @brief エラーコードの列挙型
   *
   * `ImSender` クラスで発生する可能性のあるエラーコードを定義します。
   */
  enum class ErrorCode {
    SUCCESS, /**< データ送信が成功したことを示します。 */
    INVALID_DATA_SIZE /**< データサイズが無効であることを示します。 */
  };
#endif

  /**
   * @brief データを送信するテンプレートメソッド
   *
   * このメソッドは、テンプレート型 `T` のデータを送信します。サポートされる型は
   * `int` 型、`float` 型、構造体などの直接値を保持する型に限定されています。
   * `String` 型などのポインタを内部に持つ型には対応していません。
   *
   * @tparam T 送信するデータの型
   * @param data 送信するデータ
   * @return データ送信の結果を示す `ErrorCode`
   *
   * @note データサイズが1バイトから32バイトの範囲内である必要があります。
   *       それ以外のサイズの場合は `INVALID_DATA_SIZE` が返されます。
   */
  template <typename T>
#ifdef DEBUG
  ErrorCode
#else
  void
#endif
  send(T &data) {
    DebugLogger::println("ImSender", "send", "Sending data");

#ifdef DEBUG
    // データサイズが1バイト未満または32バイトを超える場合はエラーを返す
    if (sizeof(T) < 1 || sizeof(T) > 32) {
      DebugLogger::println("ImSender", "send", "Data size is invalid");
      return ErrorCode::INVALID_DATA_SIZE;
    }
#endif

    // 送信データのプレフィックスを送信
    serial.print("TXDA ");

    // データをバイトごとに16進数形式で送信
    for (uint8_t i = 0; i < sizeof(T); i++) {
      serial.print(((uint8_t *)data)[i] >> 4, HEX);
      serial.print(((uint8_t *)data)[i] & 0xF, HEX);
    }

    // 送信終了を示す改行を送信
    serial.println();

    DebugLogger::println("ImSender", "send", "Data sent");

#ifdef DEBUG
    return ErrorCode::SUCCESS;
#endif
  }

private:
  SerialType &serial; /**< データ送信に使用するシリアル通信ストリーム */
};
