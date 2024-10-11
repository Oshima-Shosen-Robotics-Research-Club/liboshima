/**
 * @file IM920SL.h
 *
 * @brief IM920SLモジュールを使用してデータの送受信を行うためのクラス定義
 *
 * このファイルには、IM920SLモジュールを使用してデータの送受信を行うための
 * `IM920SL` クラスが定義されています。
 * このクラスは、IM920SLモジュールを使用してデータの送受信を行うための
 * 機能を提供します。
 */
#pragma once

#include <Arduino.h>
#include <MsTimer2.h>
#include <types/IsSame.h>
#include <utils/Converter.h>
#include <utils/DebugLogger.h>

#define IM_SEND_INTERVAL 60

enum class ImSenderMode : uint8_t {
  BUFFER_FULL,  ///< バッファがいっぱいの場合は即座に終了
  CAREER_SENSE, ///< キャリアセンスを検出するまで待機
  NO_WAIT       ///< データが利用できない場合は即座に終了
};

enum class ImReceiverMode : uint8_t {
  WAIT,   ///< データが利用可能になるまで待機
  NO_WAIT ///< データが利用できない場合は即座に終了
};

/**
 * @brief IM920SLクラス
 *
 * このクラスは、IM920SLモジュールを使用してデータの送受信を行うためのクラスです。
 * SerialTypeとLoggerTypeをテンプレート引数として受け取ります。
 *
 * @tparam SerialType シリアル通信の型
 * @tparam LoggerType ロガーの型（デフォルトはDebugLogger<SerialType>*）
 */
template <typename SerialType, typename LoggerType = void> class IM920SL {
public:
  /**
   * @brief コンストラクタ
   *
   * @param serial シリアル通信オブジェクト
   * @param logger ロガーオブジェクト（デフォルトはnullptr）
   */
  IM920SL(SerialType &serial, LoggerType *logger = nullptr)
      : serial(serial), logger(logger) {
    static_assert(!IsSame<DebugLogger<SerialType>, LoggerType>::value,
                  "シリアル通信がロガーと競合しています");
  }

  /**
   * @brief シリアル通信を開始する
   *
   * @param baudrate ボーレート（デフォルトは19200）
   */
  void beginSerial(unsigned long baudrate = 19200) { serial.begin(baudrate); }

  void beginTimer(void (*callback)(), uint8_t interval = 1000) {
    MsTimer2::set(interval, callback);
    MsTimer2::start();
    usesTimer = true;
  }

  /**
   * @brief データを送信するテンプレート関数
   *
   * @tparam T 送信するデータの型
   * @param data 送信するデータ
   */
  template <typename T> void send(const T &data, ImSenderMode waitmode) {

    static_assert(
        sizeof(T) >= 1 && sizeof(T) <= 32,
        "送信する型のサイズは1バイト以上32バイト以下である必要があります");

    printLog(DebugLoggerLevel::INFO, "send", "Sending data");

    constexpr uint8_t size = 5 + (sizeof(T) * 2);
    if (waitmode == ImSenderMode::NO_WAIT) {
      if (static_cast<uint8_t>(serial.availableForWrite()) < size)
        return;
    } else if (waitmode == ImSenderMode::BUFFER_FULL) {
      while (static_cast<uint8_t>(serial.availableForWrite()) < size)
        ;
    } else if (waitmode == ImSenderMode::CAREER_SENSE) {
      delay(IM_SEND_INTERVAL);
    }

    serial.print("TXDA ");
    for (uint8_t i = 0; i < sizeof(T); i++) {
      serial.print(reinterpret_cast<const uint8_t *>(&data)[i] >> 4 & 0xF, HEX);
      serial.print(reinterpret_cast<const uint8_t *>(&data)[i] & 0xF, HEX);
    }
    serial.println();

    printLog(DebugLoggerLevel::INFO, "send", "Data sent");
  }

  /**
   * @brief データを受信するテンプレート関数
   *
   * @tparam T 受信するデータの型
   * @param data 受信したデータを格納する変数
   * @param wait データが到着するまで待機するかどうか（デフォルトはfalse）
   * @return bool コロンの受信に成功した場合はtrue、それ以外はfalse
   */
  template <typename T> bool receive(T &data, ImReceiverMode mode) {

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

    // コロンを受信したらタイマーをリスタートする
    if (usesTimer) {
      MsTimer2::start();
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
  LoggerType *logger; ///< ロガーオブジェクト
  bool usesTimer = false;

  inline void printLog(DebugLoggerLevel level, const char *methodName,
                       const char *message) {
    if constexpr (!IsSame<LoggerType, void>::value) {
      logger->println(level, DebugLoggerMode::WAIT, "IM920SL", methodName,
                      message);
    }
  }

  void printLogf(DebugLoggerLevel level, const char *methodName,
                 const char *format, ...) {
    if constexpr (!IsSame<LoggerType, void>::value) {
      va_list args;
      va_start(args, format);
      logger->printlnf(level, DebugLoggerMode::WAIT, "IM920SL", methodName,
                       format, args);
      va_end(args);
    }
  }
};