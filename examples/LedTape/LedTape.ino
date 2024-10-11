#include <liboshima.h> // LEDテープ制御ライブラリをインクルード

#define NUM_LEDS 30 // LEDの数を定義
#define DATA_PIN 6 // データピンを定義

// LedTapeクラスのインスタンスを作成
// NUM_LEDS: LEDの数
// DATA_PIN: データピン
LedTape ledTape(NUM_LEDS, DATA_PIN);

void setup() {
  // 初期化処理はLedTapeクラスのコンストラクタで行われるため、
  // setup関数内では特に何もしない
}

void loop() {
  // すべてのLEDを赤色に設定
  ledTape.solidColor(LedTape::Red);
  delay(5000); // 5秒間待機

  // すべてのLEDを青色で点滅させる
  // 点滅間隔は500ミリ秒
  ledTape.blinkColor(LedTape::Blue, 500);
  delay(5000); // 5秒間待機

  // レインボーパターンを表示
  // パターンの更新間隔は20ミリ秒
  ledTape.rainbow(20);
  delay(5000); // 5秒間待機

  // すべてのLEDを赤色でチェイスパターンを表示
  // パターンの更新間隔は100ミリ秒
  ledTape.chase(LedTape::Red, 100);
  delay(5000); // 5秒間待機

  // 指定された色（紫色）でグラデーションパターンを表示
  // パターンの更新間隔は1000ミリ秒
  ledTape.gradient(LedTape::Purple, 1000);
  delay(5000); // 5秒間待機
}