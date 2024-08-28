#ifndef IM_SENDER_H
#define IM_SENDER_H

#include "utils/DebugLogger.h"
#include <SoftwareSerial.h>

// ImSender クラスの宣言
class ImSender {
public:
  // コンストラクタ: 受信ピンと送信ピン、ボーレートを設定
  ImSender(uint8_t rxPin, uint8_t txPin, long baudRate);

  // データを送信するテンプレートメソッド
  template <typename T> void send(const T &data) {
    // 送信データのプレフィックスを送信
    serial.print("TXDA ");

    // データをバッファにシリアライズ
    uint8_t buffer[sizeof(T)];
    serialize(data, buffer);

    // バッファの内容を送信
    serial.write(buffer, sizeof(T));

    // 送信終了を示す改行を送信
    serial.println();
  }

private:
  SoftwareSerial serial;

  // データをバッファにシリアライズするテンプレートメソッド
  template <typename T> void serialize(const T &data, uint8_t *buffer) {
    const uint8_t *dataPtr = (const uint8_t *)&data;
    for (size_t i = 0; i < sizeof(T); i++) {
      buffer[i] = dataPtr[i];
    }
    // シリアライズされたデータをデバッグログに出力
    DebugLogger::printf("ImSender", "serialize", "Serialized data: %d\n", data);
  }
};

#endif // IM_SENDER_H