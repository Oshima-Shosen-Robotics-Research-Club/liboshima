#include <liboshima.h> // 必要なライブラリをインクルード

// HardwareSerialを使用してDebugLoggerのインスタンスを作成
// ArduinoIDEの場合、<>内を書かないとエラーが発生する
DebugLogger<HardwareSerial> logger(Serial);

void setup() {
  // ロガーの初期化
  logger.begin();
}

void loop() {
  // ログメッセージを出力
  // レベル: INFO
  // モード: NO_WAIT
  // コンポーネント: "Main"
  // 関数: "loop"
  // メッセージ: "Hello, world!"
  logger.println(DebugLoggerLevel::INFO, DebugLoggerMode::NO_WAIT, "Main",
                 "loop", "Hello, world!");
  // 1秒間の遅延
  delay(1000);
}