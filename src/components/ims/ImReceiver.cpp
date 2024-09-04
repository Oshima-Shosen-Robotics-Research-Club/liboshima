#include "ImReceiver.h"

// コンストラクタ: 受信ピンと送信ピン、ボーレートを設定
ImReceiver::ImReceiver(uint8_t rxPin, uint8_t txPin, long baudRate)
    : serial(rxPin, txPin) {
  // シリアル通信を指定されたボーレートで開始
  serial.begin(baudRate);
}

// データが利用可能かどうかをチェックするメソッド
bool ImReceiver::available() { return serial.available(); }