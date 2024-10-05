/**
 * @file ImSender_private.h
 * @brief IM920SL通信モジュールを使用したデータ送信クラスの定義
 *
 * このファイルでは、IM920SL無線通信モジュールを使ってデータ送信を行うための
 * `ImSender_private` クラスを定義しています。`ImSender_private` クラスは
 * `HardwareSerial` または `SoftwareSerial`
 * を使用して、さまざまなデータ型の送信を行う メソッドを提供します。
 *
 * @note
 * テンプレートメソッドを使用することで、異なるデータ型を送信することが可能です。
 */

#pragma once

#include <serials/SerialPort.h>
#include <utils/DebugLogger.h>

// タイマーオーバーフロー設定で役に立つ定数（ミリ秒）
#define IM_SEND_INTERVAL 100

/**
 * @class ImSender_private
 * @brief IM920SL通信モジュールを用いたデータ送信を行うクラス
 *
 * `ImSender_private`
 * クラスは、IM920SL通信モジュールを使用してデータを送信するための
 * 機能を提供します。このクラスは `HardwareSerial` や `SoftwareSerial`
 * と連携し、 テンプレートメソッドにより様々な型のデータを送信可能です。
 */
class ImSender_private {
public:
  /**
   * @brief コンストラクタ (HardwareSerialバージョン)
   *
   * 指定された `HardwareSerial` インスタンスを使ってIM920SLモジュールとの
   * 通信を行います。
   *
   * @param serial 使用する `HardwareSerial` インスタンスの参照
   */
  ImSender_private(SerialPort &serial);

  /**
   * @brief 通信の初期化を行うメソッド
   *
   * 指定したボーレート（通信速度）でIM920SLモジュールとの通信を開始します。
   * デフォルトのボーレートは19200bpsです。
   *
   * @param baudrate 通信速度（ボーレート）。デフォルトは19200bps。
   */
  void begin(unsigned long baudrate = 19200);

  /**
   * @brief データ送信を行うテンプレートメソッド
   *
   * テンプレート型 `T` のデータを送信します。サポートされている型は `int` や
   * `float` 、構造体などの固定長のデータ型です。ポインタを持つ `String` 型
   * などには対応していません。
   *
   * @tparam T 送信するデータの型
   * @param data 送信するデータ
   */
  template <typename T> void send(const T &data) {
    static_assert(sizeof(T) >= 1 && sizeof(T) <= 32,
                  "Data size must be between 1 and 32 bytes");
    send(reinterpret_cast<const uint8_t *>(&data), sizeof(T));
  }

private:
  SerialPort &serial; /**< データ送信に使用するシリアル通信ポート */

  /**
   * @brief 内部でデータ送信を行うメソッド
   *
   * このメソッドは、データを送信します。
   *
   * @param data 送信するデータを格納したバッファ
   * @param size 送信するデータのサイズ
   */
  void send(const uint8_t *data, const size_t size);
};
