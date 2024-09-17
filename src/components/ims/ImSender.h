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

  enum ErrorCode {
    SUCCESS,
    INVALID_DATA_SIZE,
  };

  // データを送信するテンプレートメソッド
  // int型、float型、構造体のみに対応
  template <typename T> ErrorCode send(const T &data) {
    if (sizeof(T) < 1 && sizeof(T) > 32) {
      DebugLogger::println("ImSender", "send", "Data size is invalid");
      return INVALID_DATA_SIZE;
    }

    // 送信データのプレフィックスを送信
    serial.print("TXDA ");

    for (uint8_t i = 0; i < sizeof(T); i++) {
      uint8_t byte = ((uint8_t *)&data)[i];
      serial.print(byte >> 4, HEX);
      serial.print(byte & 0xf, HEX);
    }

    // 送信終了を示す改行を送信
    serial.println();

    return SUCCESS;
  }

private:
  Stream &serial;
};

#endif // IM_SENDER_H