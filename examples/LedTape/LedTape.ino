#include "components/LedTape.h"

#define NUM_LEDS 30
#define DATA_PIN 6

LedTape ledTape(NUM_LEDS, DATA_PIN);

void setup() {
  // 初期化処理はコンストラクタで行われるため、ここでは特に何もしない
}

void loop() {
  // すべてのLEDを赤色に設定
  ledTape.solidColor(LedTape::Red);
  delay(5000);

  // 青色で点滅
  ledTape.blinkColor(LedTape::Blue, 500);
  delay(5000);

  // レインボーパターンを表示
  ledTape.rainbow(20);
  delay(5000);

  // 緑色でチェイスパターンを表示
  ledTape.chase(LedTape::Red, 100);
  delay(5000);

  // 指定された色でグラデーションパターンを表示
  ledTape.gradient(LedTape::Purple, 1000);
  delay(5000);
}