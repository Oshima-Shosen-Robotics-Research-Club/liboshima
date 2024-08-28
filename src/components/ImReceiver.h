#ifndef IM_RECEIVER_H
#define IM_RECEIVER_H

#include "utils/DebugLogger.h"
#include <SoftwareSerial.h>

// ImReceiver クラスの宣言
class ImReceiver {
public:
  // コンストラクタ: 受信ピンと送信ピン、ボーレートを設定
  ImReceiver(uint8_t rxPin, uint8_t txPin, long baudRate);

  // データが利用可能かどうかをチェックするメソッド
  bool available();

  // データを受信するテンプレートメソッド
  template <typename T> bool receive(T &data) {
    // データが利用可能でない場合は false を返す
    if (!available()) {
      DebugLogger::print("ImReceiver", "receive", "No data available\n");
      return false;
    }

    String recvedStr;
    char recvedChar;

    DebugLogger::print("ImReceiver", "receive", "Waiting for data...\n");

    // データが到着するのを待ち、文字列に読み込む
    while (true) {
      recvedChar = (char)serial.read();
      if (recvedChar == '\n') {
        break;
      } else {
        recvedStr += recvedChar;
      }
    }

    DebugLogger::printf("ImReceiver", "receive", "Received data: %s\n",
                        recvedStr.c_str());

    // コロンのインデックスを見つける
    int colonIndex = recvedStr.indexOf(':');
    if (colonIndex == -1) {
      DebugLogger::print("ImReceiver", "receive", "Colon not found\n");
      return false;
    }

    // コロンの後のデータを抽出
    String hexData = recvedStr.substring(colonIndex + 1);

    // データの長さが不足している場合は false を返す
    if (hexData.length() < sizeof(T) * 2) {
      DebugLogger::print("ImReceiver", "receive", "Data length is too short\n");
      return false;
    }

    uint8_t buffer[sizeof(T)];
    // 16進数のペアをバッファに変換
    for (size_t i = 0; i < sizeof(T); i++) {
      String hexPair = hexData.substring(i * 2, i * 2 + 2);
      buffer[i] = (uint8_t)strtol(hexPair.c_str(), nullptr, 16);
    }

    // バッファをデータにデシリアライズ
    deserialize(buffer, data);
    return true;
  }

private:
  SoftwareSerial serial;

  // バッファをデータにデシリアライズするテンプレートメソッド
  template <typename T> void deserialize(uint8_t *buffer, T &data) {
    memcpy(&data, buffer, sizeof(T));
    DebugLogger::printf("ImReceiver", "deserialize", "Deserialized data: %d\n",
                        data);
  }
};

#endif // IM_RECEIVER_H