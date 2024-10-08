#include "TB67H450.h"
#include <Arduino.h>
#include <digitalWriteFast.h>

// コンストラクタ: モーター制御用のピンを設定
TB67H450::TB67H450(uint8_t in1, uint8_t in2) : in1(in1), in2(in2) {
  // ピンを出力モードに設定
  pinModeFast(in1, OUTPUT);
  pinModeFast(in2, OUTPUT);
}

// モーターを制御する内部メソッド
// PWM信号を使用してモーターを制御
void TB67H450::runAnalogue(uint8_t analogueValue1, uint8_t analogueValue2) {
  // 指定されたピンに PWM 信号を出力
  analogWrite(in1, analogueValue1);
  analogWrite(in2, analogueValue2);
}

// モーターを制御する内部メソッド
// デジタル信号を使用してモーターを制御
void TB67H450::runDigital(bool digitalValue1, bool digitalValue2) {
  // 指定されたピンにデジタル信号を出力
  digitalWriteFast(in1, digitalValue1);
  digitalWriteFast(in2, digitalValue2);
}

// 正転メソッド: モーターを前進させる
void TB67H450::forward() {
  setSpeed(1.0); // 最大出力で前進
}

// 後転メソッド: モーターを後退させる
void TB67H450::reverse() {
  setSpeed(-1.0); // 最大出力で後退
}

// モーター停止メソッド: モーターを停止させる
void TB67H450::stop() {
  setSpeed(0); // 速度を 0 に設定
}

// モーターの速度を設定するメソッド
void TB67H450::setSpeed(float rate) {
  // スピードの範囲を -1.0 から 1.0 に制限
  rate = constrain(rate, -1.0, 1.0);

  if (abs(rate) == 1.0) {
    runDigital(rate > 0, rate < 0); // 最大出力で前進または後退
  } else if (rate == 0) {
    runDigital(HIGH, HIGH); // 停止
  } else {
    // 速度に応じた PWM 値を計算
    uint8_t pwmValue = (uint8_t)(abs(rate) * 255);
    runAnalogue(rate > 0 ? pwmValue : 0, rate < 0 ? pwmValue : 0);
  }
}