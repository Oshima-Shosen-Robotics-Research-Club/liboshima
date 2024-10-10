#pragma once

#include <utils/DebugLogger.h>

#define IM_SEND_INTERVAL 60

class ImSenderBase {
public:
  enum class Mode : uint8_t {
    WAIT,   ///< データが利用可能になるまで待機
    NO_WAIT ///< データが利用できない場合は即座に終了
  };
};

/**
 * @brief IM920SL送信クラス
 *
 * このクラスは、IM920SLモジュールを使用してデータを送信するためのクラスです。
 * SerialTypeとLoggerTypeをテンプレート引数として受け取ります。
 *
 * @tparam SerialType シリアル通信の型
 * @tparam LoggerType ロガーの型（デフォルトはDebugLogger<SerialType>*）
 */
template <typename SerialType, typename LoggerType = DebugLogger<void> *>
class ImSender : public ImSenderBase {
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
  template <typename T> void send(const T &data, Mode mode) {

    static_assert(sizeof(T) >= 1 && sizeof(T) <= 32,
                  "Data size must be between 1 and 32 bytes");

    if constexpr (IsSame<decltype(logger), DebugLogger<void> *>::value)
      logger->println(DebugLogger<void>::LogLevel::INFO,
                      DebugLogger<void>::WaitMode::WAIT, "ImSender", "send",
                      "Sending data");

    if (serial.availableForWrite() < 5 + (sizeof(T) * 2)) {
      if (mode == Mode::WAIT) {
        while (serial.availableForWrite() < 5 + (sizeof(T) * 2))
          ;
      } else {
        return;
      }
    }

    serial.print("TXDA ");
    for (uint8_t i = 0; i < sizeof(T); i++) {
      serial.print(reinterpret_cast<const uint8_t *>(&data)[i] >> 4 & 0xF, HEX);
      serial.print(reinterpret_cast<const uint8_t *>(&data)[i] & 0xF, HEX);
    }
    serial.println();

    if constexpr (IsSame<decltype(logger), DebugLogger<void> *>::value)
      logger->println(DebugLogger<void>::LogLevel::INFO,
                      DebugLogger<void>::WaitMode::WAIT, "ImSender", "send",
                      "Data sent");
  }

private:
  SerialType &serial; ///< シリアル通信オブジェクトの参照
  LoggerType logger;  ///< ロガーオブジェクト
};

template <> class ImSender<void> : public ImSenderBase {};