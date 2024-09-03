#ifndef IM_RECEIVER_H
#define IM_RECEIVER_H

#include "utils/DebugLogger.h"
#include <SoftwareSerial.h>

// ImReceiver クラスの宣言
class ImReceiver {
public:
  // コンストラクタ: 受信ピンと送信ピン、ボーレートを設定
  ImReceiver(uint8_t rxPin, uint8_t txPin, long baudRate = 19200);

  // データが利用可能かどうかをチェックするメソッド
  bool available();

  // データを受信するテンプレートメソッド
  template <typename T> bool receive(T &data) {
    // データが利用可能でない場合は false を返す
    if (!available()) {
      DebugLogger::println("ImReceiver", "receive", "No data available");
      return false;
    }

    String recvedStr;
    char recvedChar;

    // 受信文字列の例："00,0001,EA:12,34,56,78"（ペイロード::受信データ）
    // 文字列の長さを計算
    int payloadLen = 11;
    int hexStrLen = sizeof(T) * 2;
    int commaCount = sizeof(T) - 1;
    int recvedStrLen = payloadLen + 1 + hexStrLen + commaCount;

    // 受信文字列を読み取る
    while (true) {
      recvedChar = serial.read();
      if (recvedChar == '\n')
        break;
      else
        recvedStr += recvedChar;

      if (recvedStr.length() > static_cast<size_t>(recvedStrLen)) {
        DebugLogger::println("ImReceiver", "receive",
                             "Received string is too long");
        return false;
      }
    }

    DebugLogger::printlnf("ImReceiver", "receive", "Received data: %s",
                          recvedStr.c_str());

    // コロンのインデックスを見つける
    int colonIndex = recvedStr.indexOf(':');
    if (colonIndex == -1) {
      DebugLogger::println("ImReceiver", "receive", "Colon not found");
      return false;
    }

    // コロンの後のデータ（"12,34,56,78"）を抽出
    String recvedData = recvedStr.substring(colonIndex + 1);

    // データが長さが適切でない場合は false を返す
    if (recvedData.length() != static_cast<size_t>(hexStrLen + commaCount)) {
      DebugLogger::println("ImReceiver", "receive", "Data length is invalid");
      return false;
    }

    uint8_t buffer[sizeof(T)];
    // 16進数のペアをバッファに変換
    for (int i = 0; i < (int)sizeof(T); i++) {
      String hexPair = recvedData.substring(i * 3, i * 3 + 2);
      buffer[i] = (uint8_t)strtol(hexPair.c_str(), nullptr, 16);
    }

    // バッファをデータにデシリアライズ
    memcpy(&data, buffer, sizeof(T));
    return true;
  }

private:
  SoftwareSerial serial;
};

#endif // IM_RECEIVER_H