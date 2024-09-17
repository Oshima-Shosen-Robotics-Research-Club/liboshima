#ifndef IM_RECEIVER_H
#define IM_RECEIVER_H

#include "utils/DebugLogger.h"
#include <SoftwareSerial.h>

#define IM_RECEIVE_INTERVAL_MILLIS                                             \
  500 // タイマーオーバーフローに最適な時間間隔(milliseconds)
#define IM_RECEIVE_INTERVAL_MICROS                                             \
  500000 // タイマーオーバーフローに最適な時間間隔(microseconds)

// ImReceiver クラスの宣言
class ImReceiver {
public:
  // コンストラクタ
  ImReceiver(HardwareSerial &serial, unsigned long baudrate = 19200);
  ImReceiver(SoftwareSerial &serial, unsigned long baudrate = 19200);

  enum ErrorCode {
    SUCCESS,
    NO_DATA_AVAILABLE,
    RECEIVED_STRING_LENGTH_INVALID,
    COLON_NOT_FOUND,
    DATA_LENGTH_INVALID,
  };

  // データが利用可能かどうかをチェックするメソッド
  bool available();

  // データを受信するテンプレートメソッド
  // int型、float型、構造体のみに対応
  template <typename T> ErrorCode receive(T &data) {
    // データが利用可能でない場合は false を返す
    if (!available()) {
      DebugLogger::println("ImReceiver", "receive", "No data available");
      return NO_DATA_AVAILABLE;
    }

    String recvedStr;

    // 受信文字列の例："00,0001,EA:12,34,56,78"（ペイロード::受信データ）
    // 文字列の長さを計算
    uint8_t payloadLen = 10;
    uint8_t hexStrLen = sizeof(T) * 2;
    uint8_t commaCount = sizeof(T) - 1;
    uint8_t recvedStrLen = payloadLen + 1 + hexStrLen + commaCount;

    // 受信文字列を読み取る("\r\n" は取取り除く)
    recvedStr = serial.readStringUntil('\n');
    recvedStr.remove(recvedStr.length() - 1);

    if (recvedStr.length() != recvedStrLen) {
      DebugLogger::println("ImReceiver", "receive",
                           "Received string length is invalid");
      return RECEIVED_STRING_LENGTH_INVALID;
    }

    DebugLogger::printlnf("ImReceiver", "receive", "Received string: %s",
                          recvedStr.c_str());

    // コロンのインデックスを見つける
    int8_t colonIndex = recvedStr.indexOf(':');
    if (colonIndex == -1) {
      DebugLogger::println("ImReceiver", "receive", "Colon not found");
      return COLON_NOT_FOUND;
    }

    // コロンの後のデータ（"12,34,56,78"）を抽出
    String recvedData = recvedStr.substring(colonIndex + 1);

    // データの長さが適切でない場合は false を返す
    if (recvedData.length() != hexStrLen + commaCount) {
      DebugLogger::println("ImReceiver", "receive", "Data length is invalid");
      return DATA_LENGTH_INVALID;
    }

    // 16進数のペアをバッファに変換
    for (uint8_t i = 0; i < sizeof(T); i++) {
      String hexPair = recvedData.substring(i * 3, i * 3 + 2);
      ((uint8_t *)&data)[i] = (uint8_t)strtol(hexPair.c_str(), nullptr, 16);
    }

    return SUCCESS;
  }

private:
  Stream &serial;
};

#endif // IM_RECEIVER_H
