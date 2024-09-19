#include "ImReceiver.h"
#include <SoftwareSerial.h>

// HardwareSerial の場合
ImReceiver::ImReceiver(HardwareSerial &serial, unsigned long baudrate)
    : serial(serial) {
  serial.begin(baudrate);
}

// SoftwareSerial の場合
ImReceiver::ImReceiver(SoftwareSerial &serial, unsigned long baudrate)
    : serial(serial) {
  serial.begin(baudrate);
}

// データが利用可能かどうかをチェックするメソッド
bool ImReceiver::available() { return serial.available(); }

// "00,0000,00:00,00,00\r\n" という形式のデータを受信する
#ifdef DEBUG
ImReceiver::ErrorCode
#else
void
#endif
ImReceiver::receive(uint8_t *data, size_t size) {
  DebugLogger::println("ImReceiver", "receive", "Receiving data");

#ifdef DEBUG
  // データが利用可能でない場合はエラーを返す
  if (!available()) {
    DebugLogger::println("ImReceiver", "receive", "No data available");
    return ErrorCode::NO_DATA_AVAILABLE;
  }
#endif

  // 受信データの読み取り
  // 最大32バイトのデータを受信する
  // "00,0000,00:01,02,03,04,05,06,07,08,09,0A,0B,0C,0D,0E,0F,10,11,12,13,14,15,16,17,18,19,1A,1B,1C,1D,1E,1F,20"
  // ペイロード = 10、コロン = 1、データ = 32 * 2、カンマ = 32 - 1 = 31
  char recvedStr[10 + 1 + 32 * 2 + 31 + 1]; // null文字を含める
  size_t length = serial.readBytesUntil('\n', recvedStr, sizeof(recvedStr) - 1);
  recvedStr[length] = '\0'; // Null-terminate the string

  // 受信文字をデバッグ出力
  DebugLogger::printlnf("ImReceiver", "receive", "Received: %s", recvedStr);

#ifdef DEBUG
  // 受信文字列の長さが予期される長さと一致しない場合はエラーを返す
  if (length != 10 + 1 + size * 2 + size - 1) {
    DebugLogger::println("ImReceiver", "receive",
                         "Received string length invalid");
    return ErrorCode::RECEIVED_STRING_LENGTH_INVALID;
  }

  if (recvedStr[10] != ':') {
    DebugLogger::println("ImReceiver", "receive", "Colon not found");
    return ErrorCode::COLON_NOT_FOUND;
  }
#endif

  // データ部分のみを抽出
  char *pos = recvedStr + 11;

#ifdef DEBUG
  // 無効な文字列が含まれている場合はエラーを返す
  if (!((pos[0] >= '0' && pos[0] <= '9') || (pos[0] >= 'A' && pos[0] <= 'F')) ||
      !((pos[1] >= '0' && pos[1] <= '9') || (pos[1] >= 'A' && pos[1] <= 'F'))) {
    DebugLogger::println("ImReceiver", "receive", "Data string invalid");
    return ErrorCode::DATA_STRING_INVALID;
  }
#endif

  // バイナリのサイズは大きくなるが、処理が増えるわけではないので、問題ないと考える
  /*
  '0' = 48, '9' = 57, 'A' = 65, 'F' = 70
  */
  constexpr uint8_t lookup[] = {
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
      17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
      34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, // パディング
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,                  // 0-9
      58, 59, 60, 61, 62, 63, 64,                             // パディング
      10, 11, 12, 13, 14, 15,                                 // A-F
  };

  for (size_t i = 0; i < size; i++) {
    uint8_t high = lookup[(uint8_t)*pos++];
    uint8_t low = lookup[(uint8_t)*pos++];

    data[i] = (high << 4) | low;

    if (*pos == ',') {
      pos++;
    }
  }

  // データをデバッグ出力
  DebugLogger::println("ImReceiver", "receive", "Data received");

#ifdef DEBUG
  return ErrorCode::SUCCESS;
#endif
}
