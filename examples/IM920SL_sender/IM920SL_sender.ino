#include <liboshima.h> // 必要なライブラリをインクルード

// HardwareSerialを使用してIM920SLのインスタンスを作成
// ArduinoIDEの場合、<>内を書かないとエラーが発生する
IM920SL<HardwareSerial> im(Serial);

void setup() {
  // 初期化処理をここに記述
}

void loop() {
  // 送信するデータを格納する変数
  int data = 0x1234;

  // データを送信する
  im.send(data, ImSendMode::USE_CARRIER_SENSE);
}