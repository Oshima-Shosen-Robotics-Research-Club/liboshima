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
ImReceiver::ErrorCode ImReceiver::receive(uint8_t *data, size_t size) {
  DebugLogger::println("ImReceiver", "receive", "Receiving data");

  // データが利用可能でない場合はエラーを返す
  if (!available()) {
    DebugLogger::println("ImReceiver", "receive", "No data available");
    return ErrorCode::NO_DATA_AVAILABLE;
  }

  // 受信データの読み取り
  // 最大32バイトのデータを受信する
  // "00,0000,00:01,02,03,04,05,06,07,08,09,0A,0B,0C,0D,0E,0F,10,11,12,13,14,15,16,17,18,19,1A,1B,1C,1D,1E,1F,20"
  // ペイロード = 10、コロン = 1、データ = 32 * 2、カンマ = 32 - 1 = 31
  char recvedStr[10 + 1 + 32 * 2 + 31 + 1]; // null文字を含める
  size_t length = serial.readBytesUntil('\n', recvedStr, sizeof(recvedStr) - 1);
  recvedStr[length] = '\0'; // Null-terminate the string

  // 受信文字をデバッグ出力
  DebugLogger::printlnf("ImReceiver", "receive", "Received: %s", recvedStr);

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

  // データ部分のみを抽出
  char *pos = recvedStr + 11;

  // 16進数のデータを手動で解析
  for (size_t i = 0; i < size; i++) {
    if (*pos >= '0' && *pos <= '9') {
      data[i] = (*pos - '0') << 4;
    } else if (*pos >= 'A' && *pos <= 'F') {
      data[i] = (*pos - 'A' + 10) << 4;
    } else {
      DebugLogger::println("ImReceiver", "receive", "Data length invalid");
      return ErrorCode::DATA_LENGTH_INVALID;
    }

    pos++;
    if (*pos >= '0' && *pos <= '9') {
      data[i] |= (*pos - '0');
    } else if (*pos >= 'A' && *pos <= 'F') {
      data[i] |= (*pos - 'A' + 10);
    } else {
      DebugLogger::println("ImReceiver", "receive", "Data length invalid");
      return ErrorCode::DATA_LENGTH_INVALID;
    }

    pos++;
    if (*pos == ',') {
      pos++;
    }
  }

  return ErrorCode::SUCCESS;
}
