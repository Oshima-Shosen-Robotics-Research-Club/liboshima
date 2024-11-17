/**
 * @file IM920SL.h
 *
 * @brief
 * IM920SLモジュールを用いてデータの送受信を行うためのクラスを定義するヘッダファイル
 *
 * このファイルでは、IM920SLモジュールを使用してデータの送受信を行う機能を持つ
 * `IM920SL` クラスを定義しています。
 * IM920SLモジュールは、シリアル通信を介してデータの送受信を行う無線通信モジュールです。本クラスは、そのモジュールを制御し、
 * データの効率的かつ正確な送受信を支援します。
 */
#pragma once

#include <Arduino.h>
#include <DebugLogger.h>
#include <MsTimer2.h>
#include <fasts/Converter.h>
#include <types/IsSame.h>

// 送信モードを定義する列挙型
/**
 * @enum ImSendMode
 * @brief データ送信時の動作モードを指定する列挙型
 *
 * IM920SLモジュールを用いてデータを送信する際に、どのように動作させるかを決定します。
 * これにより、データ送信がバッファの状態やキャリアセンスに応じて異なる動作を取ることができます。
 */
enum class ImSendMode : uint8_t {
  WAIT_FOR_BUFFER_AVAILABLE, ///< バッファが空になるまで待機
  USE_CARRIER_SENSE,         ///< キャリアセンスを考慮して送信
  EXIT_WHEN_BUFFER_FULL      ///< バッファが空になるまで待機せず、即座に終了
};

// 受信モードを定義する列挙型
/**
 * @enum ImReceiveMode
 * @brief データ受信時の動作モードを指定する列挙型
 *
 * IM920SLモジュールを用いてデータを受信する際の挙動を指定します。
 * データが受信可能になるまで待機するか、データが利用できない場合にすぐに終了するかを決定します。
 */
enum class ImReceiveMode : uint8_t {
  WAIT_FOR_SERIAL_DATA,    ///< シリアルバッファが空になるまで待機
  NO_WAIT_FOR_SERIAL_DATA, ///< バッファが空の場合は即座に終了
};

/**
 * @brief IM920SLクラス
 *
 * このクラスは、IM920SLモジュールを用いてデータの送受信を行うためのクラスです。
 * IM920SLはシリアル通信を介してデータを送信・受信する無線モジュールであり、このクラスを通じてその操作が可能です。
 *
 * @tparam SerialType シリアル通信に用いる型（例：HardwareSerial）
 * @tparam LoggerType ロガーの型（デフォルトはvoid）
 */
template <typename SerialType, typename LoggerType = void> class IM920SL {
public:
  /**
   * @brief IM920SLクラスのコンストラクタ
   *
   * SerialTypeを使ってシリアル通信を制御し、必要に応じてロガーを使用して
   * ログメッセージを出力するためのコンストラクタです。
   *
   * @param serial シリアル通信を行うオブジェクトへの参照
   * @param logger
   * ロガーオブジェクトへのポインタ（省略可能で、デフォルトはnullptr）
   */
  IM920SL(SerialType &serial, LoggerType *logger = nullptr)
      : serial(serial), logger(logger) {
    // シリアル通信とロガーの型が同じでないことを確認するためのチェック
    static_assert(!IsSame<DebugLogger<SerialType>, LoggerType>::value,
                  "シリアル通信とロガーが競合しています");
  }

  /**
   * @brief シリアル通信の開始
   *
   * 指定されたボーレートでシリアル通信を開始します。ボーレートが指定されない場合、デフォルト値として19200が使用されます。
   *
   * @param baudrate 通信ボーレート（デフォルトは19200bps）
   * @note コンストラクタでは実行できません。
   */
  void beginSerial(unsigned long baudrate = 19200) { serial.begin(baudrate); }

  /**
   * @brief データが受信されなかった場合のコールバックを設定
   *
   * 指定した時間（間隔）の間にデータが受信されなかった場合に呼び出される
   * コールバック関数を登録します。
   *
   * @param callback コールバック関数のポインタ
   * @param interval
   * データ受信が確認されなかった場合にタイマーが発火する間隔（ミリ秒単位、デフォルトは1000ms）
   */
  void onDataNotReceived(void (*callback)(), unsigned long interval = 1000) {
    // MsTimer2を使用して、指定の間隔でコールバックを実行する設定
    MsTimer2::set(interval, callback);
    MsTimer2::start();
    // コロンが受信されなかった時のコールバックを保存
    onColonNotReceived = callback;
  }

  /**
   * @brief データが受信された場合のコールバックを設定
   *
   * データが受信された際に呼び出されるコールバック関数を設定します。
   *
   * @param callback コールバック関数のポインタ
   */
  void onDataReceived(void (*callback)()) {
    onColonReceived = callback; // コロンが受信された時のコールバックを保存
  }

  /**
   * @brief データを送信するテンプレート関数
   *
   * 任意の型のデータを指定された送信モードに従って送信します。
   * 送信するデータは、型に応じて1バイトから32バイトまで対応可能です。
   *
   * @tparam T 送信するデータの型
   * @param data 送信するデータ
   * @param waitmode 送信モードを指定する（ImSendMode）
   */
  template <typename T> void send(const T &data, ImSendMode waitmode) {
    // 送信するデータのサイズが1バイト以上32バイト以下であることを確認
    static_assert(sizeof(T) >= 1 && sizeof(T) <= 32,
                  "送信するデータのサイズは1～32バイトでなければなりません");

    // ログに送信開始のメッセージを出力
    printLog(DebugLoggerLevel::INFO, "send", "Sending data");

    // 送信データのサイズを計算（シリアル通信の仕様に基づく）
    constexpr uint8_t size = 5 + (sizeof(T) * 2);

    // 指定された送信モードに従い、バッファやキャリアセンスの状態を確認
    if (waitmode == ImSendMode::EXIT_WHEN_BUFFER_FULL) {
      // バッファが空になるまで待機しない
      if (static_cast<uint8_t>(serial.availableForWrite()) < size)
        return;
    } else if (waitmode == ImSendMode::WAIT_FOR_BUFFER_AVAILABLE) {
      // バッファが空になるまで待機
      while (static_cast<uint8_t>(serial.availableForWrite()) < size)
        ;
    } else if (waitmode == ImSendMode::USE_CARRIER_SENSE) {
      // キャリアセンスを考慮して送信
      delay(60);
    }

    // データを送信
    serial.print("TXDA ");
    char hex[sizeof(T) * 2 + 1];
    Converter::toHex(reinterpret_cast<const uint8_t *>(&data), sizeof(T), hex);
    hex[sizeof(T) * 2] = '\0';
    serial.println(hex);

    // ログに送信完了のメッセージを出力
    printLog(DebugLoggerLevel::INFO, "send", "Data sent");
  }

  /**
   * @brief データを受信するテンプレート関数
   *
   * 任意の型のデータを受信し、受信したデータを指定の変数に格納します。
   * 受信モードに従って、データが利用可能になるまで待機するかどうかを決定します。
   *
   * @tparam T 受信するデータの型
   * @param data 受信したデータを格納する変数
   * @param mode 受信モードを指定する（ImReceiveMode）
   */
  template <typename T> void receive(T *data, ImReceiveMode mode) {
    // 受信するデータのサイズが1バイト以上32バイト以下であることを確認
    static_assert(sizeof(T) >= 1 && sizeof(T) <= 32,
                  "受信するデータのサイズは1～32バイトでなければなりません");

    // ログに受信開始のメッセージを出力
    printLog(DebugLoggerLevel::INFO, "receive", "Receiving data");

    // コロン（:）以前のデータを読み捨てる処理
    printLog(DebugLoggerLevel::INFO, "receive", "Reading data before colon");
    while (true) {
      if (serial.available()) {
        printLogf(DebugLoggerLevel::INFO, "receive", "Available data: %d",
                  serial.available());
        if (serial.read() == ':') {
          printLog(DebugLoggerLevel::INFO, "receive", "Colon found");
          break;
        }
      } else {
        if (mode == ImReceiveMode::WAIT_FOR_SERIAL_DATA) {
          printLog(DebugLoggerLevel::INFO, "receive",
                   "Waiting for serial data");
          while (!serial.available())
            ;
        } else if (mode == ImReceiveMode::NO_WAIT_FOR_SERIAL_DATA) {
          printLog(DebugLoggerLevel::ERROR, "receive", "No data available");
          return;
        }
      }
    }

    // コロンが受信されなかった時に呼び出される関数が登録されている場合、タイマーをリスタート
    if (onColonNotReceived) {
      MsTimer2::start();
    }

    // コロンが受信された時に呼び出される関数が登録されている場合、呼び出す
    if (onColonReceived) {
      onColonReceived();
    }

    // コロン以降のデータを読み込む
    printLog(DebugLoggerLevel::INFO, "receive", "Reading data after colon");
    static char afterColon[256]; // 大きいので念のためstatic
    for (uint8_t index = 0; index < sizeof(afterColon); index++) {
      printLog(DebugLoggerLevel::INFO, "receive", "Reading data");
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

    // dataがnullptrの場合は、受信データを読み捨てる
    if (!data) {
      printLog(DebugLoggerLevel::WARN, "receive", "Data is null");
      return;
    }

    // 受信データの変換処理
    printLog(DebugLoggerLevel::INFO, "receive", "Converting data");
    char *pos = afterColon;
    for (size_t i = 0; i < sizeof(T); i++) {
      Converter::fromHex(pos, 2, reinterpret_cast<uint8_t *>(data) + i);
      pos += 2;
      if (*pos == ',') {
        pos++;
      }
    }

    // ログに受信完了のメッセージを出力
    printLog(DebugLoggerLevel::INFO, "receive", "Data received");
  }

private:
  SerialType &serial;                     ///< シリアル通信オブジェクトの参照
  LoggerType *logger;                     ///< ロガーオブジェクトへのポインタ
  void (*onColonNotReceived)() = nullptr; ///< コロン未受信時のコールバック
  void (*onColonReceived)() = nullptr;    ///< コロン受信時のコールバック

  /**
   * @brief ログメッセージを出力するヘルパー関数
   *
   * ログレベル、メソッド名、メッセージを指定してログを出力します。ロガーが設定されていない場合は、ログは出力されません。
   *
   * @param level ログレベル（例：INFO, ERROR）
   * @param methodName メソッド名（ログの発生源となるメソッド）
   * @param message ログメッセージ
   */
  inline void printLog(DebugLoggerLevel level, const char *methodName,
                       const char *message) {
    if constexpr (!IsSame<LoggerType, void>::value) {
      logger->println(level, DebugLoggerMode::WAIT, "IM920SL", methodName,
                      message);
    }
  }

  /**
   * @brief フォーマット付きのログを出力するヘルパー関数
   *
   * ログメッセージをフォーマット形式で出力します。可変引数を使用してフォーマット文字列に値を挿入します。
   *
   * @param level ログレベル
   * @param methodName メソッド名
   * @param format フォーマット文字列
   * @param ... 可変引数
   */
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
