/**
 * @file ImReceiver.h
 * @brief IM920SL受信クラス
 *
 * このファイルには、IM920SLモジュールからデータを受信するための `ImReceiver`
 * クラスが定義されています。
 * SerialTypeとLoggerTypeをテンプレート引数として受け取ります。
 */
#pragma once

#include <types/IsSame.h>
#include <utils/Converter.h>
#include <utils/DebugLogger.h>

#define IM_RECEIVE_TIMEOUT 1000 ///< 受信タイムアウト時間（ミリ秒）

enum class ImReceiverMode : uint8_t {
    WAIT,   ///< データが利用可能になるまで待機
    NO_WAIT ///< データが利用できない場合は即座に終了
  };

/**
 * @brief IM920SL受信クラス
 *
 * このクラスは、IM920SLモジュールからデータを受信するためのクラスです。
 * SerialTypeとLoggerTypeをテンプレート引数として受け取ります。
 *
 * @tparam SerialType シリアル通信の型
 * @tparam LoggerType ロガーの型（デフォルトはDebugLogger<void>*）
 */
template <typename SerialType, typename LoggerType = DebugLogger<void> *>
class ImReceiver : public ImReceiverBase {
public:
  /**
   * @brief コンストラクタ
   *
   * @param serial シリアル通信オブジェクト
   * @param logger ロガーオブジェクト（デフォルトはnullptr）
   */
  ImReceiver(SerialType &serial, LoggerType logger = nullptr)
      : serial(serial), logger(logger) {}

  /**
   * @brief データを受信するテンプレート関数
   *
   * @tparam T 受信するデータの型
   * @param data 受信したデータを格納する変数
   * @param wait データが到着するまで待機するかどうか（デフォルトはfalse）
   * @return bool コロンの受信に成功した場合はtrue、それ以外はfalse
   */
  template <typename T> bool receive(T &data, Mode mode) {
    
    static_assert(
        sizeof(T) >= 1 && sizeof(T) <= 32,
        "受信する型のサイズは1バイト以上32バイト以下である必要があります");
    printLog(DebugLoggerLevel::INFO, "receive", "Receiving data");

    // コロン以前の文字列を読み捨てる
    printLog(DebugLoggerLevel::INFO, "receive", "Read data before colon");
    while (true) {
      if (serial.available()) {
        printLogf(DebugLoggerLevel::INFO, "receive",
                  "Number of available data: %d", serial.available());
        if (serial.read() == ':') {
          printLog(DebugLoggerLevel::INFO, "receive", "Colon found");
          break;
        }
      } else {
        if (mode == ImReceiverMode::WAIT) {
          printLog(DebugLoggerLevel::INFO, "receive", "Waiting for data");
          while (!serial.available())
            ;
        } else {
          printLog(DebugLoggerLevel::ERROR, "receive", "No data available");
          return false;
        }
      }
    }

    // コロン以降のデータを読み込む
    printLog(DebugLoggerLevel::INFO, "receive", "Read data after colon");
    char afterColon[(sizeof(T) * 2) + (sizeof(T) - 1) + 1];
    for (uint8_t index = 0; index < sizeof(afterColon); index++) {
      printLog(DebugLoggerLevel::INFO, "receive", "Read data");
      while (!serial.available())
        ;
      char c = serial.read();
      if (c == '\r') {
        printLog(DebugLoggerLevel::INFO, "receive", "Carriage return found");
        while (!serial.available())
          ;
        serial.read();
        afterColon[index] = '\0';
        break;
      }
      afterColon[index] = c;
    }

    // 受信したデータを変換する
    printLog(DebugLoggerLevel::INFO, "receive", "Convert data");
    char *pos = afterColon;
    for (size_t i = 0; i < sizeof(T); i++) {
      Converter::fromHex(pos, 2, reinterpret_cast<uint8_t *>(&data) + i);
      pos += 2;
      if (*pos == ',') {
        pos++;
      }
    }

    printLog(DebugLoggerLevel::INFO, "receive", "Data received");
    return true;
  }

private:
  SerialType &serial; ///< シリアル通信オブジェクトの参照
  inline void printLog(DebugLoggerLevel level, const char *methodName,
                       const char *message) {
    if constexpr (!IsSame<LoggerType, void>::value) {
      logger->println(level, DebugLoggerMode::WAIT, "ImReceiver", methodName,
                      message);
    }
  }

  void printLogf(DebugLoggerLevel level, const char *methodName,
                 const char *format, ...) {
    if constexpr (!IsSame<LoggerType, void>::value) {
      va_list args;
      va_start(args, format);
      logger->printlnf(level, DebugLoggerMode::WAIT, "ImReceiver", methodName,
                       format, args);
      va_end(args);
    }
  }
};

template <> class ImReceiver<void> : public ImReceiverBase {};
