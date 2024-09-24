/**
 * @file ImSender.h
 * @brief IM920SL通信モジュールを使用したデータ送信クラスの定義
 *
 * このファイルでは、IM920SL無線通信モジュールを使ってデータ送信を行うための
 * `ImSender` クラスを定義しています。`ImSender` クラスは `HardwareSerial`
 * または `SoftwareSerial` を使用して、さまざまなデータ型の送信を行う
 * メソッドを提供します。
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
 * @class ImSender
 * @brief IM920SL通信モジュールを用いたデータ送信を行うクラス
 *
 * `ImSender` クラスは、IM920SL通信モジュールを使用してデータを送信するための
 * 機能を提供します。このクラスは `HardwareSerial` や `SoftwareSerial`
 * と連携し、 テンプレートメソッドにより様々な型のデータを送信可能です。
 */
class ImSender {
public:
  /**
   * @brief コンストラクタ (HardwareSerialバージョン)
   *
   * 指定された `HardwareSerial` インスタンスを使ってIM920SLモジュールとの
   * 通信を行います。
   *
   * @param serial 使用する `HardwareSerial` インスタンスの参照
   */
  ImSender(SerialPort &serial);

#ifdef DEBUG
  /**
   * @enum ErrorCode
   * @brief データ送信時のエラーコードの列挙型
   *
   * データ送信中に発生する可能性のあるエラーを表します。
   */
  enum class ErrorCode {
    SUCCESS, /**< データ送信が成功したことを示します。 */
    INVALID_DATA_SIZE /**< 送信するデータのサイズが無効であることを示します。 */
  };
#endif

  /**
   * @brief 通信の初期化を行うメソッド
   *
   * 指定したボーレート（通信速度）でIM920SLモジュールとの通信を開始します。
   * デフォルトのボーレートは19200bpsです。
   *
   * @param baudrate 通信速度（ボーレート）。デフォルトは19200bps。
   */
  void begin(unsigned long baudrate = 19200);

#ifdef DEBUG
  /**
   * @brief データ送信を行うテンプレートメソッド（デバッグモード）
   *
   * テンプレート型 `T` のデータを送信します。サポートされている型は `int` や
   * `float` 、構造体などの固定長のデータ型です。ポインタを持つ `String` 型
   * などには対応していません。
   *
   * @tparam T 送信するデータの型
   * @param data 送信するデータ
   * @return データ送信の結果を示す `ErrorCode`
   *
   * @note データのサイズは1バイトから32バイトの範囲内である必要があります。
   *       それ以外のサイズの場合、`INVALID_DATA_SIZE` が返されます。
   */
  template <typename T> ErrorCode send(const T &data) {
    return send(reinterpret_cast<const uint8_t *>(&data), sizeof(T));
  }
#else
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
    send(reinterpret_cast<const uint8_t *>(&data), sizeof(T));
  }
#endif

private:
  SerialPort &serial; /**< データ送信に使用するシリアル通信ポート */

#ifdef DEBUG
  /**
   * @brief 内部でデータ送信を行うメソッド（デバッグモード）
   *
   * このメソッドは、データを送信し、結果としてエラーコードを返します。
   *
   * @param data 送信するデータを格納したバッファ
   * @param size 送信するデータのサイズ
   * @return 送信結果を示すエラーコード（`ErrorCode`）
   */
  ErrorCode
#else
  /**
   * @brief 内部でデータ送信を行うメソッド
   *
   * このメソッドは、データを送信します。
   *
   * @param data 送信するデータを格納したバッファ
   * @param size 送信するデータのサイズ
   */
  void
#endif
  send(const uint8_t *data, size_t size);
};
