#include "ImSender.h"
#include <SoftwareSerial.h>

ImSender::ImSender(SerialPort &serial) : serial(serial) {}

void ImSender::begin(unsigned long baudrate) { serial.begin(baudrate); }

// "TXDA 000000\r\n" という形式でデータを送信する
#ifdef DEBUG
ImSender::ErrorCode
#else
void
#endif
ImSender::send(const uint8_t *data, size_t size) {
  Debug.println("ImSender", "send", "Sending data");

#ifdef DEBUG
  // データサイズが1バイト未満または32バイトを超える場合はエラーを返す
  if (size < 1 || size > 32) {
    Debug.println("ImSender", "send", "Data size is invalid");
    return ErrorCode::INVALID_DATA_SIZE;
  }
#endif

  // 送信データのプレフィックスを送信
  serial.print("TXDA ");

  // データをバイトごとに16進数形式で送信
  for (uint8_t i = 0; i < size; i++) {
    serial.print(data[i] >> 4);
    serial.print(data[i] & 0xF);
  }

  // 送信終了を示す改行を送信
  serial.println();

  // 送信データをデバッグ出力
  Debug.println("ImSender", "send", "Data sent");

#ifdef DEBUG
  return ErrorCode::SUCCESS;
#endif
}