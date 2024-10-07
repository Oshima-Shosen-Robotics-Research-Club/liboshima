#pragma once

#include <utils/DebugLogger.h>

#define IM_SEND_INTERVAL 60

/**
 * @brief IM920SL送信クラス
 *
 * このクラスは、IM920SLモジュールを使用してデータを送信するためのクラスです。
 * SerialTypeとLoggerTypeをテンプレート引数として受け取ります。
 *
 * @tparam SerialType シリアル通信の型
 * @tparam LoggerType ロガーの型（デフォルトはDebugLogger<SerialType>*）
 */
template <typename SerialType, typename LoggerType = DebugLogger<SerialType> *>
class ImSender {
public:
  /**
   * @brief コンストラクタ
   *
   * @param serial シリアル通信オブジェクト
   * @param logger ロガーオブジェクト（デフォルトはnullptr）
   */
  ImSender(SerialType &serial, LoggerType logger = nullptr)
      : serial(serial), logger(logger) {}

  /**
   * @brief データを送信するテンプレート関数
   *
   * @tparam T 送信するデータの型
   * @param data 送信するデータ
   */
  template <typename T> void send(const T &data) {
    static_assert(sizeof(T) >= 1 && sizeof(T) <= 32,
                  "Data size must be between 1 and 32 bytes");
    if (logger)
      logger->println("ImSender", "send", "Sending data");

    serial.print("TXDA ");
    for (uint8_t i = 0; i < sizeof(T); i++) {
      serial.print(reinterpret_cast<const uint8_t *>(&data)[i] >> 4 & 0xF, HEX);
      serial.print(reinterpret_cast<const uint8_t *>(&data)[i] & 0xF, HEX);
    }
    serial.println();

    if (logger)
      logger->println("ImSender", "send", "Data sent");
  }

private:
  SerialType &serial; ///< シリアル通信オブジェクトの参照
  LoggerType logger;  ///< ロガーオブジェクト
};