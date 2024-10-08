#include "LedTape.h"

// テンプレート引数は変数に対応していないため
#define ADD_LEDS_CASE(pin)                                                     \
  case pin:                                                                    \
    FastLED.addLeds<WS2812B, pin>(leds, numLeds);                              \
    break;

// コンストラクタ：LEDの数とデータピンを指定し、LEDをセットアップ
LedTape::LedTape(uint8_t numLeds, const uint8_t dataPin) : numLeds(numLeds) {
  leds = new CRGB[numLeds]; // LED配列を動的に割り当て

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

LedTape::~LedTape() {
  delete[] leds; // 動的メモリを解放
}

// 単色で全てのLEDを光らせる
void LedTape::solidColor(uint32_t color) {
  fill_solid(leds, numLeds, CRGB(color));
  FastLED.show();
}

// LEDを点滅させる
void LedTape::blinkColor(uint32_t color, unsigned long delayTime) {
  solidColor(color); // 全部同じ色で光らせる
  delay(delayTime);
  solidColor(CRGB::Black); // 消す
  delay(delayTime);
}

// レインボーパターンで光らせる
void LedTape::rainbow(unsigned long delayTime) {
  for (uint8_t j = 0; j < 256; j++) {
    for (uint8_t i = 0; i < numLeds; i++) {
      leds[i] = CHSV((i + j) % 256, 255, 255); // HSV色空間で色を変える
    }
    FastLED.show();
    delay(delayTime);
  }
}

// チェイスパターンで光らせる
void LedTape::chase(uint32_t color, unsigned long delayTime) {
  for (uint8_t i = 0; i < numLeds; i++) {
    leds[i] = color; // 1つずつ色を設定
    FastLED.show();
    delay(delayTime);
    leds[i] = CRGB::Black; // 消す
  }
}

// 指定された色を基にしたグラデーションパターン
void LedTape::gradient(uint32_t baseColor, unsigned long delayTime) {
  CRGB color = CRGB(baseColor); // 指定された色をCRGBオブジェクトに変換
  uint8_t maxBrightness = 255;

  // 色相を基に、グラデーションを生成
  for (uint8_t i = 0; i < numLeds; i++) {
    float factor = (float)i / numLeds; // グラデーションの割合

    // ベースの色に基づいて、明るさを段階的に変化させる
    leds[i] = color.fadeToBlackBy((1.0f - factor) * maxBrightness);
  }
  FastLED.show();
  delay(delayTime);
}