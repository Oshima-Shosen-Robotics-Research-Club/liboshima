#include "ImSender.h"
#include <SoftwareSerial.h>

ImSender::ImSender(HardwareSerial &serial, unsigned long baudrate)
    : serial(serial) {
  serial.begin(baudrate);
}

ImSender::ImSender(SoftwareSerial &serial, unsigned long baudrate)
    : serial(serial) {
  serial.begin(baudrate);
}

ImSender::ErrorCode ImSender::send(const uint8_t *data, size_t size) {
  // データサイズが1バイト未満または32バイトを超える場合はエラーを返す
  if (size < 1 || size > 32) {
    DebugLogger::println("ImSender", "send", "Data size is invalid");
    return INVALID_DATA_SIZE;
  }

  // 送信データのプレフィックスを送信
  serial.print("TXDA ");

  // データをバイトごとに16進数形式で送信
  for (uint8_t i = 0; i < size; i++) {
    serial.print(data[i] >> 4, HEX);
    serial.print(data[i] & 0xF, HEX);
  }

  // 送信終了を示す改行を送信
  serial.println();
  return SUCCESS;
}