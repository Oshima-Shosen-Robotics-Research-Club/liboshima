#include "ImReceiver.h"
#include <SoftwareSerial.h>

const uint8_t ImReceiver::lookup[71] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
    34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, // パディング
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,                  // 0-9
    58, 59, 60, 61, 62, 63, 64,                             // パディング
    10, 11, 12, 13, 14, 15,                                 // A-F
};

// HardwareSerial の場合
ImReceiver::ImReceiver(SerialPort &serial, unsigned long baudrate)
    : serial(serial) {
  serial.begin(baudrate);
}

// データが利用可能かどうかをチェックするメソッド
bool ImReceiver::available() { return serial.available(); }

// "00,0000,00:00,00,00\r\n" という形式のデータを受信する
#if defined(DEBUG)
ImReceiver::ErrorCode
#else
void
#endif
ImReceiver::receive(uint8_t *data, size_t size) {
  Debug.println("ImReceiver", "receive", "Receiving data");

#if defined(DEBUG)
  // データが利用可能でない場合はエラーを返す
  if (!available()) {
    Debug.println("ImReceiver", "receive", "No data available");
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
  Debug.printlnf("ImReceiver", "receive", "Received: %s", recvedStr);

#if defined(DEBUG)
  // 受信文字列の長さが予期される長さと一致しない場合はエラーを返す
  if (length != 10 + 1 + size * 2 + size - 1) {
    Debug.printlnf("ImReceiver", "receive",
                   "Received string length invalid: %d", length);
    return ErrorCode::RECEIVED_STRING_LENGTH_INVALID;
  }

  if (recvedStr[10] != ':') {
    Debug.println("ImReceiver", "receive", "Colon not found");
    return ErrorCode::COLON_NOT_FOUND;
  }
#endif

  // データ部分のみを抽出
  char *pos = recvedStr + 11;

#if defined(DEBUG)
  // 無効な文字列が含まれている場合はエラーを返す
  if (!((pos[0] >= '0' && pos[0] <= '9') || (pos[0] >= 'A' && pos[0] <= 'F')) ||
      !((pos[1] >= '0' && pos[1] <= '9') || (pos[1] >= 'A' && pos[1] <= 'F'))) {
    Debug.println("ImReceiver", "receive", "Data string invalid");
    return ErrorCode::DATA_STRING_INVALID;
  }
#endif

  for (size_t i = 0; i < size; i++) {
    uint8_t high = lookup[(uint8_t)*pos++];
    uint8_t low = lookup[(uint8_t)*pos++];

    data[i] = (high << 4) | low;

    if (*pos == ',') {
      pos++;
    }
  }

  // データをデバッグ出力
  Debug.println("ImReceiver", "receive", "Data received");

#if defined(DEBUG)
  return ErrorCode::SUCCESS;
#endif
}