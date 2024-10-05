#include "ImSender_private.h"

ImSender_private::ImSender_private(SerialPort &serial) : serial(serial) {}

void ImSender_private::begin(unsigned long baudrate) { serial.begin(baudrate); }

// "TXDA 000000\r\n" という形式でデータを送信する
void ImSender_private::send(const uint8_t *data, const size_t size) {
  Logger.println("ImSender_private", "send", "Sending data");

  // 送信データのプレフィックスを送信
  serial.print("TXDA ");

  // データをバイトごとに16進数形式で送信
  for (uint8_t i = 0; i < size; i++) {
    serial.print(data[i] >> 4, 16);
    serial.print(data[i] & 0xF, 16);
  }

  // 送信終了を示す改行を送信
  serial.println();

  // 送信データをデバッグ出力
  Logger.println("ImSender_private", "send", "Data sent");
}