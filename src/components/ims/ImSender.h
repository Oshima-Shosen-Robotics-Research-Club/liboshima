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

#ifndef IM_SENDER_H
#define IM_SENDER_H

#include "utils/DebugLogger.h"
#include <SoftwareSerial.h>

// データ送信に適した時間間隔 (ミリ秒単位)
// この定義は、データ送信間隔の設定や調整に使用される可能性があります。
// ユーザー側で調整することで、送信頻度を制御できます。
#define IM_SEND_INTERVAL 60

/**
 * @class ImSender
 * @brief IM920SL通信モジュールを用いたデータ送信を行うクラス
 *
 * `ImSender` クラスは、IM920SL通信モジュールを使用してデータを送信するための
 * 機能を提供します。このクラスは `HardwareSerial` または `SoftwareSerial` と
 * 連携し、テンプレートメソッドを使用して様々な型のデータを送信できます。
 */
class ImSender {
public:
  /**
   * @brief コンストラクタ (HardwareSerial バージョン)
   *
   * `HardwareSerial` インスタンスを使用して通信を行います。
   *
   * @param serial 使用する `HardwareSerial` インスタンスの参照
   * @param baudrate 通信速度（ボーレート）。デフォルト値は19200。
   */
  ImSender(HardwareSerial &serial, unsigned long baudrate = 19200);

  /**
   * @brief コンストラクタ (SoftwareSerial バージョン)
   *
   * `SoftwareSerial` インスタンスを使用して通信を行います。
   *
   * @param serial 使用する `SoftwareSerial` インスタンスの参照
   * @param baudrate 通信速度（ボーレート）。デフォルト値は19200。
   */
  ImSender(SoftwareSerial &serial, unsigned long baudrate = 19200);

  /**
   * @enum ErrorCode
   * @brief エラーコードの列挙型
   *
   * `ImSender` クラスで発生する可能性のあるエラーコードを定義します。
   */
  enum ErrorCode {
    SUCCESS, /**< データ送信が成功したことを示します。 */
    INVALID_DATA_SIZE /**< データサイズが無効であることを示します。 */
  };

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
  template <typename T> ErrorCode send(const T &data) {
    // データサイズが1バイト未満または32バイトを超える場合はエラーを返す
    if (sizeof(T) < 1 || sizeof(T) > 32) {
      DebugLogger::println("ImSender", "send", "Data size is invalid");
      return INVALID_DATA_SIZE;
    }

    // 送信データのプレフィックスを送信
    serial.print("TXDA ");

    // データをバイトごとに16進数形式で送信
    for (uint8_t i = 0; i < sizeof(T); i++) {
      uint8_t byte = ((uint8_t *)&data)[i];
      serial.print(byte >> 4, HEX);
      serial.print(byte & 0xf, HEX);
    }

    // 送信終了を示す改行を送信
    serial.println();

    return SUCCESS;
  }

private:
  Stream &serial; /**< データ送信に使用するシリアル通信ストリーム */
};

#endif // IM_SENDER_H
