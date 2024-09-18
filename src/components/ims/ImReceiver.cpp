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

// "00,0000,00:00,00,00" という形式のデータを受信する
ImReceiver::ErrorCode ImReceiver::receive(uint8_t *data, size_t size) {
  // データが利用可能でない場合はエラーを返す
  if (!available()) {
    DebugLogger::println("ImReceiver", "receive", "No data available");
    return ErrorCode::NO_DATA_AVAILABLE;
  }

  String recvedStr;

  // 受信文字列の長さを計算
  uint8_t payloadLen = 10;
  uint8_t hexStrLen = size * 2;
  uint8_t commaCount = size - 1;
  uint8_t recvedStrLen = payloadLen + 1 + hexStrLen + commaCount;

  // 受信文字列を読み取り、改行文字を削除する
  recvedStr = serial.readStringUntil('\n');
  recvedStr.remove(recvedStr.length() - 1);

  // 受信文字列の長さが無効な場合はエラーを返す
  if (recvedStr.length() != recvedStrLen) {
    DebugLogger::println("ImReceiver", "receive",
                         "Received string length is invalid");
    return ErrorCode::RECEIVED_STRING_LENGTH_INVALID;
  }

  DebugLogger::printlnf("ImReceiver", "receive", "Received string: %s",
                        recvedStr.c_str());

  // コロンのインデックスを見つける
  int8_t colonIndex = recvedStr.indexOf(':');
  if (colonIndex == -1) {
    DebugLogger::println("ImReceiver", "receive", "Colon not found");
    return ErrorCode::COLON_NOT_FOUND;
  }

  // コロンの後のデータ（例: "12,34,56,78"）を抽出する
  String recvedData = recvedStr.substring(colonIndex + 1);

  // データの長さが無効な場合はエラーを返す
  if (recvedData.length() != hexStrLen + commaCount) {
    DebugLogger::println("ImReceiver", "receive", "Data length is invalid");
    return ErrorCode::DATA_LENGTH_INVALID;
  }

  // 16進数のペアをデータバッファに変換する
  for (uint8_t i = 0; i < size; i++) {
    String hexPair = recvedData.substring(i * 3, i * 3 + 2);
    data[i] = (uint8_t)strtol(hexPair.c_str(), nullptr, 16);
  }

  return ErrorCode::SUCCESS;
}