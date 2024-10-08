/**
 * @file ImReceiver.h
 * @brief IM920SL受信クラス
 *
 * このファイルには、IM920SLモジュールからデータを受信するための `ImReceiver`
 * クラスが定義されています。
 * SerialTypeとLoggerTypeをテンプレート引数として受け取ります。
 */
#pragma once

#include <utils/Converter.h>
#include <utils/DebugLogger.h>

#define IM_RECEIVE_TIMEOUT 1000 ///< 受信タイムアウト時間（ミリ秒）

/**
 * @brief エラーコードを表す列挙型
 */
enum class ReceiveErrorCode {
  SUCCESS,                        ///< 成功
  NO_DATA_AVAILABLE,              ///< データが利用できない
  RECEIVED_STRING_LENGTH_INVALID, ///< 受信した文字列の長さが無効
  COLON_NOT_FOUND,                ///< コロンが見つからない
};

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
   * @brief データを受信するテンプレート関数
   *
   * @tparam T 受信するデータの型
   * @param data 受信したデータを格納する変数
   * @param wait データが到着するまで待機するかどうか（デフォルトはfalse）
   * @return bool コロンの受信に成功した場合はtrue、それ以外はfalse
   */
  template <typename T> bool receive(T &data, bool wait = false) {
    static_assert(sizeof(T) >= 1 && sizeof(T) <= 32,
                  "Data size must be between 1 and 32 bytes");

    printLog("Start receiving data");

    // コロン以前の文字列を読み捨てる
    printLog("Discard data before colon");
    while (true) {
      if (serial.available()) {
        printLogf("Number of available data: %d", serial.available());
        if (serial.read() == ':') {
          printLog("Colon found");
          break;
        }
      } else {
        if (wait) {
          printLog("Wait for data");
          while (!serial.available())
            ;
        } else {
          printLog("No data available");
          return false;
        }
      }
    }

    // コロン以降のデータを読み込む
    printLog("Read data after colon");
    char afterColon[(sizeof(T) * 2) + (sizeof(T) - 1) + 1];
    for (uint8_t index = 0; index < sizeof(afterColon); index++) {
      printLog("Read data");
      while (!serial.available())
        ;
      char c = serial.read();
      if (c == '\r') {
        printLog("Carriage return found");
        while (!serial.available())
          ;
        serial.read();
        afterColon[index] = '\0';
        break;
      }
      afterColon[index] = c;
    }

    // 受信したデータを変換する
    printLog("Convert data");
    char *pos = afterColon;
    for (size_t i = 0; i < sizeof(T); i++) {
      Converter::fromHex(pos, 2, reinterpret_cast<uint8_t *>(&data) + i);
      pos += 2;
      if (*pos == ',') {
        pos++;
      }
    }

    printLog("Data received");
    return true;
  }

private:
  SerialType &serial; ///< シリアル通信オブジェクトの参照
  LoggerType logger;  ///< ロガーオブジェクト
  void printLog(const char *message) {
    if (logger)
      logger->println("ImReceiver", "receive", message);
  }
  void printLogf(const char *format, ...) {
    if (logger) {
      logger->printlnf("ImReceiver", "receive", format, ...);
    }
  }
};