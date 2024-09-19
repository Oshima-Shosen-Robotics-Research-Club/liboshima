/**
 * @file ImReceiver.h
 * @brief IM920SL通信モジュールを用いたデータ受信のためのクラス定義
 *
 * このファイルには、IM920SL通信モジュールを用いてデータを受信するための
 * `ImReceiver` クラスが定義されています。`ImReceiver`
 * クラスは、`HardwareSerial` または `SoftwareSerial`
 * と連携してデータを受信し、受信したデータを指定した
 * 型に変換する機能を提供します。
 *
 * @note このクラスは、テンプレートメソッドを使用して様々な型のデータを
 *       受信することができます。
 */

#ifndef IM_RECEIVER_H
#define IM_RECEIVER_H

#include "utils/DebugLogger.h"
#include <SoftwareSerial.h>

// タイマーオーバーフローに最適な時間間隔 (ミリ秒単位)
// この定義は受信タイミングの調整に使用される可能性があります。
// ユーザーが調整することで、受信間隔を制御できます。
#define IM_RECEIVE_INTERVAL_MILLIS 500

// タイマーオーバーフローに最適な時間間隔 (マイクロ秒単位)
// この定義は受信タイミングの調整に使用される可能性があります。
// ユーザーが調整することで、受信間隔を制御できます。
#define IM_RECEIVE_INTERVAL_MICROS 500000

/**
 * @class ImReceiver
 * @brief IM920SL通信モジュールを用いたデータ受信を行うクラス
 *
 * `ImReceiver` クラスは、IM920SL通信モジュールを使用してデータを受信し、
 * 受信したデータを指定した型に変換するための機能を提供します。このクラスは
 * `HardwareSerial` または `SoftwareSerial` と連携し、テンプレートメソッドを
 * 使用してさまざまな型のデータを受信することができます。
 */
class ImReceiver {
public:
  /**
   * @brief コンストラクタ (HardwareSerial バージョン)
   *
   * `HardwareSerial` インスタンスを使用して通信を行います。
   *
   * @param serial 使用する `HardwareSerial` インスタンスの参照
   * @param baudrate 通信速度（ボーレート）。デフォルト値は19200。
   */
  ImReceiver(HardwareSerial &serial, unsigned long baudrate = 19200);

  /**
   * @brief コンストラクタ (SoftwareSerial バージョン)
   *
   * `SoftwareSerial` インスタンスを使用して通信を行います。
   *
   * @param serial 使用する `SoftwareSerial` インスタンスの参照
   * @param baudrate 通信速度（ボーレート）。デフォルト値は19200。
   */
  ImReceiver(SoftwareSerial &serial, unsigned long baudrate = 19200);

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

  /**
   * @brief データが利用可能かどうかをチェックするメソッド
   *
   * このメソッドは、受信バッファにデータが利用可能かどうかを確認します。
   *
   * @return データが利用可能であれば `true`、そうでなければ `false`
   * を返します。
   */
  bool available();

  /**
   * @brief データを受信するテンプレートメソッド
   *
   * このメソッドは、テンプレート型 `T` のデータを受信し、指定された型に
   * 変換します。サポートされる型は `int` 型、`float` 型、構造体などの
   * 直接値を保持する型に限定されています。
   *
   * @tparam T 受信するデータの型
   * @param data 受信したデータを格納する変数の参照
   * @return データ受信の結果を示す `ErrorCode`
   *
   * @note 受信データはコロン `:` で区切られた形式であると想定しています。
   *       受信文字列の長さが予期される長さと一致しない場合や、データの
   *       長さが無効である場合は、エラーコードが返されます。
   */
  template <typename T>
#ifdef DEBUG
  ErrorCode
#else
  void
#endif
  receive(T &data) {
#ifdef DEBUG
    return
#endif
        receive(reinterpret_cast<uint8_t *>(&data), sizeof(T));
  }

private:
  Stream &serial; /**< データ受信に使用するシリアル通信ストリーム */

#ifdef DEBUG
  ErrorCode
#else
  void
#endif
  receive(uint8_t *data, size_t size);
};

#endif // IM_RECEIVER_H
