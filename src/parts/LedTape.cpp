#include "LedTape.h"

// テンプレート引数は変数に対応していないため、マクロを使用してケースを追加
#define ADD_LEDS_CASE(pin)                                                     \
  case pin:                                                                    \
    FastLED.addLeds<WS2812B, pin>(leds, numLeds);                              \
    break;

// コンストラクタ：LEDの数とデータピンを指定し、LEDをセットアップ
// numLeds: 使用するLEDの数
// dataPin: データピンの番号
LedTape::LedTape(uint8_t numLeds, const uint8_t dataPin) : numLeds(numLeds) {
  // LED配列を動的に割り当て
  leds = new CRGB[numLeds];

  // データピンに基づいてLEDを追加
  // メモリーがもったいないい（泣）
  switch (dataPin) {
    ADD_LEDS_CASE(1)
    ADD_LEDS_CASE(2)
    ADD_LEDS_CASE(3)
    ADD_LEDS_CASE(4)
    ADD_LEDS_CASE(5)
    ADD_LEDS_CASE(6)
    ADD_LEDS_CASE(7)
    ADD_LEDS_CASE(8)
    ADD_LEDS_CASE(9)
    ADD_LEDS_CASE(10)
    ADD_LEDS_CASE(11)
    ADD_LEDS_CASE(12)
    ADD_LEDS_CASE(13)
    ADD_LEDS_CASE(14)
    ADD_LEDS_CASE(15)
    ADD_LEDS_CASE(16)
    ADD_LEDS_CASE(17)
    ADD_LEDS_CASE(18)
    ADD_LEDS_CASE(19)
  default:
    break;
  }
}

// デストラクタ：動的に割り当てたメモリを解放
LedTape::~LedTape() {
  delete[] leds; // 動的メモリを解放
}

// 単色で全てのLEDを光らせる
// color: 表示する色（32ビットのRGB値）
void LedTape::solidColor(uint32_t color) {
  // 全てのLEDを指定された色で塗りつぶす
  fill_solid(leds, numLeds, CRGB(color));
  // LEDの状態を表示
  FastLED.show();
}

// LEDを点滅させる
// color: 点滅させる色（32ビットのRGB値）
// delayTime: 点滅の間隔（ミリ秒）
void LedTape::blinkColor(uint32_t color, unsigned long delayTime) {
  solidColor(color);       // 全部同じ色で光らせる
  delay(delayTime);        // 指定された時間だけ待機
  solidColor(CRGB::Black); // 消す
  delay(delayTime);        // 指定された時間だけ待機
}

// レインボーパターンで光らせる
// delayTime: 各色の表示間隔（ミリ秒）
void LedTape::rainbow(unsigned long delayTime) {
  // 色相を変化させながらLEDを光らせる
  for (uint8_t j = 0; j < 256; j++) {
    for (uint8_t i = 0; i < numLeds; i++) {
      // HSV色空間で色を変える
      leds[i] = CHSV((i + j) % 256, 255, 255);
    }
    // LEDの状態を表示
    FastLED.show();
    // 指定された時間だけ待機
    delay(delayTime);
  }
}

// チェイスパターンで光らせる
// color: チェイスさせる色（32ビットのRGB値）
// delayTime: 各LEDの表示間隔（ミリ秒）
void LedTape::chase(uint32_t color, unsigned long delayTime) {
  // LEDを1つずつ光らせる
  for (uint8_t i = 0; i < numLeds; i++) {
    leds[i] = color; // 1つずつ色を設定
    // LEDの状態を表示
    FastLED.show();
    // 指定された時間だけ待機
    delay(delayTime);
    leds[i] = CRGB::Black; // 消す
  }
}

// 指定された色を基にしたグラデーションパターン
// baseColor: グラデーションの基になる色（32ビットのRGB値）
// delayTime: グラデーションの表示間隔（ミリ秒）
void LedTape::gradient(uint32_t baseColor, unsigned long delayTime) {
  // 指定された色をCRGBオブジェクトに変換
  CRGB color = CRGB(baseColor);
  uint8_t maxBrightness = 255; // 最大の明るさ

  // 色相を基に、グラデーションを生成
  for (uint8_t i = 0; i < numLeds; i++) {
    // グラデーションの割合を計算
    float factor = (float)i / numLeds;

    // ベースの色に基づいて、明るさを段階的に変化させる
    leds[i] = color.fadeToBlackBy((1.0f - factor) * maxBrightness);
  }
  // LEDの状態を表示
  FastLED.show();
  // 指定された時間だけ待機
  delay(delayTime);
}