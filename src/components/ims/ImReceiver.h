/**
 * @file ImReceiver.h
 * @brief IM920SL通信モジュールを用いたデータ受信クラスの宣言
 *
 * このファイルは、IM920SL無線モジュールを使ってデータ受信を行うクラス
 * `ImReceiver`
 * の定義を提供します。このクラスを使用してデータの受信および処理が可能です。
 */

#pragma once

#include <serials/SerialPort.h>
#include <utils/DebugLogger.h>

// タイマーオーバーフロー設定で役に立つ定数（ミリ秒）
#define IM_RECEIVE_INTERVAL_MILLIS 500

// タイマーオーバーフロー設定で役に立つ定数（マイクロ秒）
#define IM_RECEIVE_INTERVAL_MICROS 500000

/**
 * @class ImReceiver
 * @brief IM920SL通信モジュールを用いたデータ受信クラス
 *
 * `ImReceiver` クラスは、IM920SL通信モジュールを使ってデータを受信するための
 * 機能を提供します。`HardwareSerial` や `SoftwareSerial` を使用してデータの
 * 受信を管理し、テンプレートメソッドによって様々な型のデータを効率的に
 * 受信することができます。
 */
class ImReceiver {
public:
  /**
   * @brief コンストラクタ (HardwareSerialバージョン)
   *
   * このコンストラクタは、指定された `HardwareSerial` インスタンスを用いて
   * IM920SLモジュールからのデータ受信を行います。
   *
   * @param serial 使用する `HardwareSerial` インスタンスの参照
   */
  ImReceiver(SerialPort &serial);

#if defined(DEBUG)
  /**
   * @enum ErrorCode
   * @brief エラーコードの定義
   *
   * この列挙型は、データ受信中に発生する可能性のあるエラーを表します。
   */
  enum class ErrorCode {
    SUCCESS, /**< データ受信が成功したことを示します。 */
    NO_DATA_AVAILABLE, /**< データが利用できないことを示します。 */
    RECEIVED_STRING_LENGTH_INVALID, /**<
                                       受信文字列の長さが無効であることを示します。
                                     */
    COLON_NOT_FOUND,                /**< 受信データ内にコロン `:`
                                       が見つからないことを示します。 */
    DATA_STRING_INVALID, /**< 受信データ文字列が無効であることを示します。 */
  };
#endif

  /**
   * @brief 通信の初期化を行うメソッド
   *
   * 指定されたボーレート（通信速度）で、IM920SLモジュールとの通信を開始します。
   * デフォルトのボーレートは19200bpsです。
   *
   * @param baudrate 通信速度（ボーレート）。デフォルト値は19200。
   */
  void begin(unsigned long baudrate = 19200);

  /**
   * @brief 受信可能なデータのバイト数を取得
   *
   * 受信バッファにあるデータのバイト数を返します。主に、データが
   * 受信可能かどうかを確認するために使用されます。
   *
   * @return 利用可能なバイト数
   */
  uint8_t available();

#if defined(DEBUG)
  /**
   * @brief データを受信して型に変換するテンプレートメソッド
   *
   * テンプレート型 `T`
   * で指定されたデータを受信し、指定した型の変数に格納します。 データは、コロン
   * `:` で区切られた形式で受信されることを想定しています。
   *
   * @tparam T 受信するデータの型（例: `int`、`float`、構造体など）
   * @param data 受信したデータを格納する変数の参照
   * @return エラーコード（`ErrorCode`）を返し、受信結果を示します。
   */
  template <typename T> ErrorCode receive(T &data) {
    return receive(reinterpret_cast<uint8_t *>(&data), sizeof(T));
  }
#else
  /**
   * @brief データを受信して型に変換するテンプレートメソッド
   *
   * テンプレート型 `T`
   * で指定されたデータを受信し、指定した型の変数に格納します。
   * 受信データは、コロン `:` で区切られた形式を前提としています。
   *
   * @tparam T 受信するデータの型（例: `int`、`float`、構造体など）
   * @param data 受信したデータを格納する変数の参照
   */
  template <typename T> void receive(T &data) {
    receive(reinterpret_cast<uint8_t *>(&data), sizeof(T));
  }
#endif

private:
  SerialPort &serial; /**< データ受信に使用するシリアル通信ストリーム */

#if defined(DEBUG)
  /**
   * @brief データを受信してバッファに格納するメソッド
   *
   * @param data 受信したデータを格納するバッファ
   * @param size 受信するデータのサイズ
   * @return エラーコード（`ErrorCode`）を返し、受信結果を示します。
   */
  ErrorCode receive(uint8_t *data, size_t size);
#else
  /**
   * @brief データを受信してバッファに格納するメソッド
   *
   * @param data 受信したデータを格納するバッファ
   * @param size 受信するデータのサイズ
   */
  void receive(uint8_t *data, size_t size);
#endif
};
