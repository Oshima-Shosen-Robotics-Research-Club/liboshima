#include <SoftwareSerial.h> // 必要なライブラリをインクルード
#include <liboshima.h>      // 必要なライブラリをインクルード

// RXピンとTXピンの定義
#define RX_PIN 0
#define TX_PIN 0

// SoftwareSerialのインスタンスを作成
SoftwareSerial softSerial(RX_PIN, TX_PIN);

// HardwareSerialを使用してIM920SLのインスタンスを作成
// ArduinoIDEの場合、<>内を書かないとエラーが発生する
IM920SL<HardwareSerial> im(Serial);

void setup() {
  // 初期化処理をここに記述
}

void loop() {
  // 受信するデータを格納する変数
  int data;

  // データを受信する
  // モード: WAIT
  im.receive(&data, ImReceiveMode::WAIT);

  // 受信したデータを16進数で表示
  softSerial.print(data, HEX); // "1234"
}