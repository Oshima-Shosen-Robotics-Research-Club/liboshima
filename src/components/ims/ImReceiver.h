/**
 * @file ImReceiver.h
 * @brief IM920SL受信クラス
 * 
 * このファイルには、IM920SLモジュールからデータを受信するための `ImReceiver` クラスが定義されています。
 * SerialTypeとLoggerTypeをテンプレート引数として受け取ります。
 */
#pragma once

#include <utils/Converter.h>
#include <utils/DebugLogger.h>

#define IM_RECEIVE_INTERVAL_MILLIS 500
#define IM_RECEIVE_INTERVAL_MICROS 500000

/**
 * @brief IM920SL受信クラス
 *
 * このクラスは、IM920SLモジュールからデータを受信するためのクラスです。
 * SerialTypeとLoggerTypeをテンプレート引数として受け取ります。
 *
 * @tparam SerialType シリアル通信の型
 * @tparam LoggerType ロガーの型（デフォルトはDebugLogger<SerialType>*）
 */
template <typename SerialType, typename LoggerType = DebugLogger<SerialType> *>
class ImReceiver {
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
   * @brief エラーコードを表す列挙型
   */
  enum class ErrorCode {
    SUCCESS,                        ///< 成功
    NO_DATA_AVAILABLE,              ///< データが利用できない
    RECEIVED_STRING_LENGTH_INVALID, ///< 受信した文字列の長さが無効
    COLON_NOT_FOUND,                ///< コロンが見つからない
  };

  /**
   * @brief データを受信するテンプレート関数
   *
   * @tparam T 受信するデータの型
   * @param data 受信したデータを格納する変数
   * @return ErrorCode エラーコード
   */
  template <typename T> ErrorCode receive(T &data) {
    static_assert(sizeof(T) >= 1 && sizeof(T) <= 32,
                  "Data size must be between 1 and 32 bytes");

    if (logger)
      logger->println("ImReceiver", "receive", "Receiving data");

    if (!serial.available()) {
      if (logger)
        logger->println("ImReceiver", "receive", "No data available");
      return ErrorCode::NO_DATA_AVAILABLE;
    }

    size_t length = 0;
    char c;
    while (true) {
      while (!serial.available())
        ;
      c = serial.read();
      if (c == '\r') {
        while (!serial.available())
          ;
        c = serial.read();
        recvedLine[length] = '\0';
        break;
      }
      recvedLine[length++] = c;
    }

    if (logger)
      logger->printlnf("ImReceiver", "receive", "Received: %s", recvedLine);

    if (length != 10 + 1 + sizeof(T) * 2 + sizeof(T) - 1) {
      if (logger)
        logger->printlnf("ImReceiver", "receive",
                         "Received string length invalid: %d", length);
      return ErrorCode::RECEIVED_STRING_LENGTH_INVALID;
    }

    if (recvedLine[10] != ':') {
      if (logger)
        logger->println("ImReceiver", "receive", "Colon not found");
      return ErrorCode::COLON_NOT_FOUND;
    }

    char *pos = recvedLine + 11;
    for (size_t i = 0; i < sizeof(T); i++) {
      Converter::fromHex(pos, 2, reinterpret_cast<uint8_t *>(&data) + i);
      pos += 2;
      if (*pos == ',') {
        pos++;
      }
    }

    if (logger)
      logger->println("ImReceiver", "receive", "Data received");
    return ErrorCode::SUCCESS;
  }

private:
  SerialType &serial;    ///< シリアル通信オブジェクトの参照
  LoggerType logger;     ///< ロガーオブジェクト
  char recvedLine[0xFF]; ///< 受信した文字列を格納するバッファ
};