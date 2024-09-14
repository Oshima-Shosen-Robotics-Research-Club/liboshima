#ifndef LED_TAPE_H
#define LED_TAPE_H

#include <FastLED.h>

class LedTape {
public:
  // コンストラクタでLEDの数と信号ピンを初期化し、LEDをセットアップ
  LedTape(int numLeds, int dataPin);
  ~LedTape();

  // 複数の光り方パターン
  void solidColor(uint32_t color);                // 単色で光らせる
  void blinkColor(uint32_t color, int delayTime); // 点滅させる
  void rainbow(int delayTime);                    // レインボーパターン
  void chase(uint32_t color, int delayTime);      // チェイスパターン
  void gradient(uint32_t baseColor, int delayTime); // グラデーションパターン

private:
  int numLeds; // LEDの数
  CRGB *leds;  // LED配列
};

#endif // LED_TAPE_H