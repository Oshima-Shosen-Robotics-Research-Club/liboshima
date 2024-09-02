#ifndef IM_SENDER_H
#define IM_SENDER_H

#include "utils/DebugLogger.h"
#include <SoftwareSerial.h>

// ImSender クラスの宣言
class ImSender {
public:
  // コンストラクタ: 受信ピンと送信ピン、ボーレートを設定
  ImSender(uint8_t rxPin, uint8_t txPin, long baudRate = 19200);

  // データを送信するテンプレートメソッド
  template <typename T> void send(const T &data) {
    // 送信データのプレフィックスを送信
    serial.print("TXDA ");

    // データをバッファにシリアライズ
    uint8_t buffer[sizeof(T)];
    memccpy(buffer, &data, sizeof(T));

    // バッファの内容を送信
    serial.write(buffer, sizeof(T));

    // 送信終了を示す改行を送信
    serial.println();
  }

private:
  SoftwareSerial serial;
};

#endif // IM_SENDER_H