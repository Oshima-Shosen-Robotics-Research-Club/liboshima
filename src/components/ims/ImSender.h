// 通信モジュールIM920SLを用いた通信(送信)を行うためのクラス
#ifndef IM_SENDER_H
#define IM_SENDER_H

#include "utils/DebugLogger.h"
#include <SoftwareSerial.h>

// 最適な時間間隔(ms)
#define IM_SEND_INTERVAL 60

// ImSender クラスの宣言
class ImSender {
public:
  ImSender(HardwareSerial &serial, unsigned long baudrate = 19200);
  ImSender(SoftwareSerial &serial, unsigned long baudrate = 19200);

  // データを送信するテンプレートメソッド
  // int型、float型、構造体のみに対応
  template <typename T> void send(const T &data) {
    // 送信データのプレフィックスを送信
    serial.print("TXDA ");

    for (uint8_t i = 0; i < sizeof(T); i++) {
      uint8_t byte = ((uint8_t *)&data)[i];
      serial.print(byte >> 4, HEX);
      serial.print(byte & 0xf, HEX);
    }

    // 送信終了を示す改行を送信
    serial.println();
  }

private:
  Stream &serial;
};

#endif // IM_SENDER_H