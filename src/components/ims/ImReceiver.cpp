#include "ImReceiver.h"
#include <utils/Converter.h>

// HardwareSerial の場合
ImReceiver::ImReceiver(SerialPort &serial) : serial(serial) {}

void ImReceiver::begin(unsigned long baudrate) { serial.begin(baudrate); }

// データが利用可能かどうかをチェックするメソッド
uint8_t ImReceiver::available() { return serial.available(); }

// "00,0000,00:00,00,00\r\n" という形式のデータを受信する
#if defined(DEBUG)
ImReceiver::ErrorCode
#else
void
#endif
ImReceiver::receive(uint8_t *data, size_t size) {
  Logger.println("ImReceiver", "receive", "Receiving data");

#if defined(DEBUG)
  // データが利用可能でない場合はエラーを返す
  if (!available()) {
    Logger.println("ImReceiver", "receive", "No data available");
    return ErrorCode::NO_DATA_AVAILABLE;
  }
#endif

  // 受信データの読み取り
  // 最大32バイトのデータを受信する
  // "00,0000,00:01,02,03,04,05,06,07,08,09,0A,0B,0C,0D,0E,0F,10,11,12,13,14,15,16,17,18,19,1A,1B,1C,1D,1E,1F,20"
  // ペイロード = 10、コロン = 1、データ = 32 * 2、カンマ = 32 - 1 = 31
  char recvedStr[10 + 1 + 32 * 2 + 31 + 1]; // null文字を含める
  size_t length = serial.readBytesUntil('\r', recvedStr, sizeof(recvedStr) - 1);
  recvedStr[length] = '\0'; // Null-terminate the string
  while (!available())
    ;
  serial.read(); // 改行コード'\r\n'を読み飛ばす

  // 受信文字をデバッグ出力
  Logger.printlnf("ImReceiver", "receive", "Received: %s", recvedStr);

  // 受信文字列の長さが予期される長さと一致しない場合はエラーを返す
  if (length != 10 + 1 + size * 2 + size - 1) {
    Logger.printlnf("ImReceiver", "receive",
                    "Received string length invalid: %d", length);
#if defined(DEBUG)
    return ErrorCode::RECEIVED_STRING_LENGTH_INVALID;
#else
    return;
#endif
  }

  if (recvedStr[10] != ':') {
    Logger.println("ImReceiver", "receive", "Colon not found");
#if defined(DEBUG)
    return ErrorCode::COLON_NOT_FOUND;
#else
    return;
#endif
  }

  // データ部分のみを抽出
  char *pos = recvedStr + 11;

#if defined(DEBUG)
  // 無効な文字列が含まれている場合はエラーを返す
  if (!((pos[0] >= '0' && pos[0] <= '9') || (pos[0] >= 'A' && pos[0] <= 'F')) ||
      !((pos[1] >= '0' && pos[1] <= '9') || (pos[1] >= 'A' && pos[1] <= 'F'))) {
    Logger.println("ImReceiver", "receive", "Data string invalid");
    return ErrorCode::DATA_STRING_INVALID;
  }
#endif

  for (size_t i = 0; i < size; i++) {
    Converter::fromHex(pos, 2, &data[i]);
    pos += 2;

    if (*pos == ',') {
      pos++;
    }
  }

  // データをデバッグ出力
  Logger.println("ImReceiver", "receive", "Data received");

#if defined(DEBUG)
  return ErrorCode::SUCCESS;
#endif
}
