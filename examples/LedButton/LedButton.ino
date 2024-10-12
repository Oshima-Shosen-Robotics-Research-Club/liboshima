#include <liboshima.h> // ボタンとLED制御ライブラリをインクルード

// ボタンとLEDのインスタンスを作成
// ボタンのピン番号を0に設定
// LEDのピン番号を1に設定
Button button(0);
Led led(1);

void setup() {
  // 初期化処理は特に必要ないため、setup関数内では何もしない
}

void loop() {
  // ボタンが押されたかどうかをチェック
  if (button.isPressed()) {
    // ボタンが押された場合、LEDを点灯
    led.on();
  } else {
    // ボタンが押されていない場合、LEDを消灯
    led.off();
  }
}